using System;
using System.Collections.Generic;
using System.Text;
using RubikCube;
using System.Collections;
using System.IO;
using System.Xml.Serialization;
using RubikCube;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace CubeSolver
{
    public class RobotCubeSolver
    {
        #region Claws
        /// <summary>
        /// Position of the robot claw 1.
        /// </summary>
        public const CubeFaceType Claw_L = CubeFaceType.L;

        /// <summary>
        /// Position of the robot claw 2.
        /// </summary>
        public const CubeFaceType Claw_F = CubeFaceType.F;
        #endregion

        #region Properties
        /// <summary>
        /// Cube to be solved.
        /// </summary>
        private Cube Cube;
        #endregion

        #region Constructors
        public RobotCubeSolver(Cube cube)
        {
            Cube = cube;
        }
        #endregion

        #region Solving Methods
        /// <summary>
        /// Solves the cube and returns the list of the movements to be done.
        /// </summary>
        /// <returns>List of movements to be sent to the robot</returns>
        public List<Movement> Solve(String inputCubeString)
        {
            // isto não existirá! é apenas para testarmos enviando como entrada do Solver um cubo em formato string
            // para testarmos o algoritmo dos movimentos... na implementação final, esta linha
            // No algoritmo real, passo da visão já fornecerá a estrutura do cubo montada
            Cube = TranslateInputStringToCube(inputCubeString);

            // valida o cubo, primeiramente
            if (!Cube.Validate())
                return new List<Movement>();

            // traduz cubo para a entrada da DLL
            inputCubeString = TranslateCubeToSolverInput(Cube);

            // chama dll em C
            String outputOfSolver = SolveRubikCube(inputCubeString);

            // traduz movimentos retornados para uma lista de Movement (movements)
            // os RotateFaceMovement.PositionFace não estão preenchidos, pois nesta etapa, 
            // ainda não se tem esta informação. eles serão preenchdiso no AdjustMovementsBasedOnTheClaws
            List<Movement> movements = TranslateStringToListOfMovements(outputOfSolver);

            // add rotation movements to bring faces to the robot claws
            AdjustMovementsBasedOnTheClaws(movements);

            return movements;
        }
        #endregion

        // Este método foi apenas criado para usarmos para a interface traduzir um string para uma estrutura de cubo
        // Não será necessário depois, na implementação final
        public Cube TranslateInputStringToCube(String input)
        {
            Dictionary<CubeFace, CubeFaceType> faces = new Dictionary<RubikCube.CubeFace,RubikCube.CubeFaceType>();

            for (int pos = 0; pos < input.Length; pos++)
            {
                // pega a posicao da face
                CubeFaceType positionFace = (CubeFaceType) Enum.Parse(typeof(CubeFaceType), input[pos++].ToString());
                pos++;

                Dictionary<CubeFaceletType, CubeFaceColor> facelets = new Dictionary<CubeFaceletType, CubeFaceColor>();
                facelets.Add(CubeFaceletType.UpLeft, (CubeFaceColor) Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.UpMid, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.UpRight, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.MidLeft, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.Center, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.MidRight, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.DownLeft, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.DownMid, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));
                facelets.Add(CubeFaceletType.DownRight, (CubeFaceColor)Enum.Parse(typeof(CubeFaceColor), input[pos++].ToString()));

                CubeFace face = new CubeFace(facelets);
                faces.Add(face, positionFace);
            }
            
            return new Cube(faces);
        }
            
        #region Private Members
        /// <summary>
        /// Adjust movements to bring the faces to be turned to some of the claws
        /// </summary>
        /// <param name="movements"></param>
        private void AdjustMovementsBasedOnTheClaws(List<Movement> movements)
        {
            List<Movement> finalMovements = new List<Movement>();

            for (int i = 0; i < movements.Count - 1; i++)
            {
                finalMovements.AddRange(AdjustMovement(movements[i], movements[i+1]));
            }
            finalMovements.AddRange(AdjustMovement(movements[movements.Count - 1], new RotateFaceMovement(CubeFaceColor.G, CubeFaceType.B)));
            movements.Clear();
            movements.AddRange(finalMovements);
        }

        /// <summary>
        /// Add a rotation movement if needed
        /// </summary>
        /// <param name="movement">Kind of movement to know what face must be brought to some of the claws</param>
        /// <param name="nextMovement">Next movement to optimize and reduce the number of cube rotations</param>
        /// <returns></returns>
        private List<Movement> AdjustMovement(Movement movement, Movement nextMovement)
        {
            List<Movement> adjustedMovements = new List<Movement>();

            if ((movement is RotateFaceMovement) && (nextMovement is RotateFaceMovement))
            {
                RotateFaceMovement mov = (RotateFaceMovement) movement;
                RotateFaceMovement nextMov = (RotateFaceMovement) nextMovement;
                mov.PositionFace = Cube[Cube[mov.Face]];
                BringFaceToSomeClaw(mov.PositionFace, Cube[Cube[nextMov.Face]], adjustedMovements);
                mov.PositionFace = Cube[Cube[mov.Face]];
            }
            
            // coloca o próprio movimento, no final
            
            adjustedMovements.Add(movement);
            return adjustedMovements;
        }

        /// <summary>
        /// Adds the rotation movement.
        /// </summary>
        /// <param name="positionFace">Position of the face to be turned</param>
        /// <param name="movements">List of movements to be concatenated of the new movement</param>
        private void BringFaceToSomeClaw(CubeFaceType positionFace, CubeFaceType nextPositionFace, List<Movement> movements)
        {
            // se face não está diretamente ligada a uma das garras, leva a face para a garra
            if (!positionFace.Equals(Claw_L) && !positionFace.Equals(Claw_F))
            {
                RotateCubeMovement mov = new RotateCubeMovement();

                switch (positionFace)
                {
                    case CubeFaceType.U:
                        if (nextPositionFace.Equals(CubeFaceType.F))
                        {
                            mov.Axis = CoordinateAxis.X;
                            mov.Type = TurnType.HalfTurnLeft;
                        }
                        else
                        {
                            mov.Axis = CoordinateAxis.Y;
                            mov.Type = TurnType.HalfTurnRight;
                        }
                        break;
                    case CubeFaceType.B:
                        mov.Axis = CoordinateAxis.Y;
                        mov.Type = TurnType.FullTurn;
                        break;
                    case CubeFaceType.R:
                        mov.Axis = CoordinateAxis.X;
                        mov.Type = TurnType.FullTurn;
                        break;
                    case CubeFaceType.D:
                        if (nextPositionFace.Equals(CubeFaceType.F))
                        {
                            mov.Axis = CoordinateAxis.X;
                            mov.Type = TurnType.HalfTurnRight;
                        }
                        else
                        {
                            mov.Axis = CoordinateAxis.Y;
                            mov.Type = TurnType.HalfTurnLeft;
                        }
                        break;
                }
                // turns the representation of the cube (very important)
                Cube.TurnCube(mov);
                // adds the new movement to the list of movements
                movements.Add(mov);
            }
        }

        /// <summary>
        /// Translates a string with the algorithm output pattern to a list of movements
        /// </summary>
        /// <param name="value">string to be parsed</param>
        /// <returns>list of movements</returns>
        private List<Movement> TranslateStringToListOfMovements(String value)
        {
            List<Movement> movements = new List<Movement>();
            RotateFaceMovement mov = new RotateFaceMovement();
            bool isClockwise = true;
            bool hasMovement = false;

            for (int i = 0; i < value.Length; i++)
            {
                switch (value[i])
                {
                    case 'U':
                        mov.Face = (Cube[CubeFaceType.U]).Center;
                        hasMovement = true;
                        break;
                    case 'D':
                        mov.Face = (Cube[CubeFaceType.D]).Center;
                        hasMovement = true;
                        break;
                    case 'B':
                        mov.Face = (Cube[CubeFaceType.B]).Center;
                        hasMovement = true;
                        break;
                    case 'F':
                        mov.Face = (Cube[CubeFaceType.F]).Center;
                        hasMovement = true;
                        break;
                    case 'R':
                        mov.Face = (Cube[CubeFaceType.R]).Center;
                        hasMovement = true;
                        break;
                    case 'L':
                        mov.Face = (Cube[CubeFaceType.L]).Center;
                        hasMovement = true;
                        break;
                    case '\'':
                        mov.Type = TurnType.HalfTurnLeft;
                        isClockwise = false;
                        break;
                    case '2':
                        mov.Type = TurnType.FullTurn;
                        isClockwise = false;
                        break;
                    case ' ':
                        if (isClockwise)
                        {
                            mov.Type = TurnType.HalfTurnRight;
                        }
                        isClockwise = true;                        
                        movements.Add(mov);
                        mov = new RotateFaceMovement();
                        break;
                }
            }
            if (isClockwise)
            {
                mov.Type = TurnType.HalfTurnRight;
            }
            if (hasMovement)
            {
                movements.Add(mov);
            }
            return movements;
        }

        private String TranslateCubeToSolverInput(Cube cube)
        {
            String input = "";

            foreach (KeyValuePair<CubeFace, CubeFaceType> entry in Cube.CubeMap)
            {
                input += entry.Value.ToString() + ":";

                Dictionary<CubeFaceletType, CubeFaceColor> facelets = entry.Key.getFacelets();
                input += facelets[CubeFaceletType.UpLeft].ToString();
                input += facelets[CubeFaceletType.UpMid].ToString();
                input += facelets[CubeFaceletType.UpRight].ToString();
                input += facelets[CubeFaceletType.MidLeft].ToString();
                input += facelets[CubeFaceletType.Center].ToString();
                input += facelets[CubeFaceletType.MidRight].ToString();
                input += facelets[CubeFaceletType.DownLeft].ToString();
                input += facelets[CubeFaceletType.DownMid].ToString();
                input += facelets[CubeFaceletType.DownRight].ToString();
                input += " ";
            }

            return input;
        }
#endregion

        #region Solver DLL
        [DllImport("KociembaRubikSolver.dll", EntryPoint = "SolveRubikCube")]
        public static extern unsafe IntPtr SolveRubikCube(void* cubeAsString);

        private static unsafe string SolveRubikCube(string cubeAsString)
        {
            IntPtr filePtr = IntPtr.Zero;
            try
            {
                filePtr = Marshal.StringToHGlobalAnsi(cubeAsString);
                IntPtr t = SolveRubikCube(filePtr.ToPointer());
                return Marshal.PtrToStringAnsi(t); ;
            }
            finally
            {
                if (filePtr != IntPtr.Zero)
                    Marshal.FreeHGlobal(filePtr);
            }
        }
        #endregion
    }
}

