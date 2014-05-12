using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    public class Cube
    {
        /// <summary>
        /// Mapping of the positions of the cube with the face colors.
        /// </summary>
        public Dictionary<CubeFace, CubeFaceType> CubeMap { get; set; }

        public Cube()
        {
            CubeMap = new Dictionary<CubeFace, CubeFaceType>();
        }

        public Cube(Dictionary<CubeFace, CubeFaceType> cube)
        {
            CubeMap = cube;
        }

        public void TurnCube(RotateCubeMovement movement)
        {
            if (CubeMap.Count == 6)
            {
                if (movement.Axis.Equals(CoordinateAxis.X))
                {
                    RotateCubeByXAxis(movement.Type);
                }
                else if (movement.Axis.Equals(CoordinateAxis.Y))
                {
                    RotateCubeByYAxis(movement.Type);
                }
                else if (movement.Axis.Equals(CoordinateAxis.Z))
                {
                    RotateCubeByZAxis(movement.Type);
                }
            }
        }

        private void RotateCubeByXAxis(TurnType type)
        {
            Dictionary<CubeFace, CubeFaceType> newCube = new Dictionary<CubeFace, CubeFaceType>();

            if (type.Equals(TurnType.HalfTurnRight))
            {
                newCube.Add(this[CubeFaceType.U], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.D);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.L);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.F], CubeFaceType.F);
            }
            else if (type.Equals(TurnType.HalfTurnLeft))
            {
                newCube.Add(this[CubeFaceType.U], CubeFaceType.L);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.D);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.F], CubeFaceType.F);
            }
            else
            {
                newCube.Add(this[CubeFaceType.U], CubeFaceType.D);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.L);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.F], CubeFaceType.F);
            }

            CubeMap.Clear();
            CubeMap = newCube;
        }

        private void RotateCubeByYAxis(TurnType type)
        {
            Dictionary<CubeFace, CubeFaceType> newCube = new Dictionary<CubeFace, CubeFaceType>();

            if (type.Equals(TurnType.HalfTurnRight))
            {
                newCube.Add(this[CubeFaceType.U], CubeFaceType.F);
                newCube.Add(this[CubeFaceType.F], CubeFaceType.D);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.L);
            }
            else if (type.Equals(TurnType.HalfTurnLeft))
            {
                newCube.Add(this[CubeFaceType.U], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.D);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.F);
                newCube.Add(this[CubeFaceType.F], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.L);
            }
            else
            {
                newCube.Add(this[CubeFaceType.U], CubeFaceType.D);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.F);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.F], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.L);
            }

            CubeMap.Clear();
            CubeMap = newCube;
        }

        private void RotateCubeByZAxis(TurnType type)
        {
            Dictionary<CubeFace, CubeFaceType> newCube = new Dictionary<CubeFace, CubeFaceType>();

            if (type.Equals(TurnType.HalfTurnRight))
            {
                newCube.Add(this[CubeFaceType.F], CubeFaceType.L);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.F);
                newCube.Add(this[CubeFaceType.U], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.D);
            }
            else if (type.Equals(TurnType.HalfTurnLeft))
            {
                newCube.Add(this[CubeFaceType.F], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.L);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.F);
                newCube.Add(this[CubeFaceType.U], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.D);
            }
            else
            {
                newCube.Add(this[CubeFaceType.F], CubeFaceType.B);
                newCube.Add(this[CubeFaceType.L], CubeFaceType.R);
                newCube.Add(this[CubeFaceType.B], CubeFaceType.F);
                newCube.Add(this[CubeFaceType.R], CubeFaceType.L);
                newCube.Add(this[CubeFaceType.U], CubeFaceType.U);
                newCube.Add(this[CubeFaceType.D], CubeFaceType.D);
            }

            CubeMap.Clear();
            CubeMap = newCube;
        }

        /// <summary>
        /// Gets the correpondent face.
        /// </summary>
        /// <param name="color">The position of the face</param>
        /// <returns>Returns the face position.</returns>
        /// <exception cref="IndexOutOfRangeException"></exception>
        public CubeFace this[CubeFaceType type]
        {
            get
            {
                foreach (KeyValuePair<CubeFace, CubeFaceType> entry in CubeMap)
                {
                    if (entry.Value.Equals(type))
                        return entry.Key;
                }
                throw new IndexOutOfRangeException();
            }
        }

        /// <summary>
        /// Gets the correpondent face.
        /// </summary>
        /// <param name="color">The color of the face</param>
        /// <returns>Returns the face position.</returns>
        /// <exception cref="IndexOutOfRangeException"></exception>
        public CubeFace this[CubeFaceColor color]
        {
            get
            {
                foreach (KeyValuePair<CubeFace, CubeFaceType> entry in CubeMap)
                {
                    if (entry.Key.Center.Equals(color))
                        return entry.Key;
                }
                throw new IndexOutOfRangeException();
            }
        }

        /// <summary>
        /// Gets the correpondent face position.
        /// </summary>
        /// <param name="color">The face</param>
        /// <returns>Returns the face position.</returns>
        /// <exception cref="IndexOutOfRangeException"></exception>
        public CubeFaceType this[CubeFace face]
        {
            get
            {
                foreach (KeyValuePair<CubeFace, CubeFaceType> entry in CubeMap)
                {
                    if (entry.Key.Equals(face))
                        return entry.Value;
                }
                throw new IndexOutOfRangeException();
            }
        }

        public bool Validate()
        {
            Dictionary<CubeFaceColor, int> numberOfColors = new Dictionary<CubeFaceColor, int>();
            numberOfColors.Add(CubeFaceColor.B, 0);
            numberOfColors.Add(CubeFaceColor.G, 0);
            numberOfColors.Add(CubeFaceColor.W, 0);
            numberOfColors.Add(CubeFaceColor.Y, 0);
            numberOfColors.Add(CubeFaceColor.R, 0);
            numberOfColors.Add(CubeFaceColor.O, 0);

            foreach (KeyValuePair<CubeFace, CubeFaceType> entry in CubeMap)
            {
                if (!entry.Key.Validate())
                    return false;

                foreach (CubeFaceColor color in entry.Key.getFacelets().Values)
                {
                    numberOfColors[color]++;
                }
            }

            foreach (int count in numberOfColors.Values)
            {
                if (count != 9)
                    return false;
            }

            if (CubeMap.Count != 6)
                return false;

            return true;
        }
    }
}
