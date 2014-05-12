/*
 * Coordinates conventions
 * X:
 *      Positive -> F FACE CLOCKWISE
 *      Negative -> F FACE COUNTER-CLOCKWISE
 * Y:
 *      Positive -> L FACE CLOCKWISE
 *      Negative -> L FACE COUNTER-CLOCKWISE
 * Z:
 *      Positive -> U FACE CLOCKWISE
 *      Negative -> U FACE COUNTER-CLOCKWISE
 */
using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    public class VisualCube
    {
        #region Fields

        #region Default Moves Variations
        public readonly Coordinate[,] default_moves = new Coordinate[,]
        {
            {//From U
                new Coordinate(CoordinateAxis.X, 0), //To U
                new Coordinate(CoordinateAxis.Y, 180), //To D
                new Coordinate(CoordinateAxis.X, -90), //To L
                new Coordinate(CoordinateAxis.X, +90), //To R
                new Coordinate(CoordinateAxis.Y, +90), //To F
                new Coordinate(CoordinateAxis.Y, -90) //To B
            },
            {//From D
                new Coordinate(CoordinateAxis.Y, 180), //To U
                new Coordinate(CoordinateAxis.Y, 0), //To D
                new Coordinate(CoordinateAxis.X, +90), //To L
                new Coordinate(CoordinateAxis.X, -90), //To R
                new Coordinate(CoordinateAxis.Y, -90), //To F
                new Coordinate(CoordinateAxis.Y, +90) //To B
            },
            {//From L
                new Coordinate(CoordinateAxis.X, +90), //To U
                new Coordinate(CoordinateAxis.X, -90), //To D
                new Coordinate(CoordinateAxis.X, 0), //To L
                new Coordinate(CoordinateAxis.X, 180), //To R
                new Coordinate(CoordinateAxis.Z,-90), //To F
                new Coordinate(CoordinateAxis.Z,+90) //To B
            },
            {//From R
                new Coordinate(CoordinateAxis.X, -90), //To U
                new Coordinate(CoordinateAxis.X, +90), //To D
                new Coordinate(CoordinateAxis.X, 180), //To L
                new Coordinate(CoordinateAxis.X, 0), //To R
                new Coordinate(CoordinateAxis.Z,+90), //To F
                new Coordinate(CoordinateAxis.Z,-90) //To B
            },
            {//From F
                new Coordinate(CoordinateAxis.Y,-90), //To U
                new Coordinate(CoordinateAxis.Y,+90), //To D
                new Coordinate(CoordinateAxis.Z,+90), //To L
                new Coordinate(CoordinateAxis.Z,-90), //To R
                new Coordinate(CoordinateAxis.Y,0), //To F
                new Coordinate(CoordinateAxis.Y,180) //To B
            },
            {//From B
                new Coordinate(CoordinateAxis.Y,+90), //To U
                new Coordinate(CoordinateAxis.Y,-90), //To D
                new Coordinate(CoordinateAxis.Z,-90), //To L
                new Coordinate(CoordinateAxis.Z,+90), //To R
                new Coordinate(CoordinateAxis.Y,180), //To F
                new Coordinate(CoordinateAxis.Y,0) //To B
            }
        };
        #endregion

        #region Block Matrix conversion

        private CubeFaceletType[] clkwse_blkmtrix = new CubeFaceletType[]
        {
            CubeFaceletType.UpRight,//UL to
            CubeFaceletType.MidRight,//UMid to
            CubeFaceletType.DownRight,//UR to
            CubeFaceletType.UpMid,//MidL to
            CubeFaceletType.Center,//Center to
            CubeFaceletType.DownMid,//MidR to
            CubeFaceletType.UpLeft,//DL to
            CubeFaceletType.MidLeft,//DMid to
            CubeFaceletType.DownLeft//DR to
        };

        #endregion

        private List<VisualCubeFace> _faces = new List<VisualCubeFace>();

        #endregion

        #region Props

        /// <summary>
        /// Gets the correpondent face.
        /// </summary>
        /// <param name="type">Type of the face</param>
        /// <returns>Returns the face.</returns>
        /// <exception cref="IndexOutOfRangeException"></exception>
        public VisualCubeFace this[CubeFaceType type]
        {
            get
            {
                VisualCubeFace face = null;
                foreach (VisualCubeFace item in _faces)
                {
                    if (item.FaceType == type)
                    {
                        face = item;
                        break;
                    }
                }
                if (face != null)
                    return face;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        #endregion

        #region Methods

        #region FaceList Manipulation

        /// <summary>
        /// Adds/Udates a face to the cube
        /// </summary>
        /// <param name="face">The face to be added/Udated</param>
        public void AddFace(VisualCubeFace face)
        {
            int foundIndex = -1;
            for (int i = 0; i < _faces.Count; i++)
            {
                if (_faces[i].FaceType == face.FaceType)
                {
                    foundIndex = i;
                    break;
                }
            }
            if (foundIndex == -1)
                _faces.Add(face.Clone());
            else
            {
                _faces[foundIndex] = face.Clone();
            }
        }

        /// <summary>
        /// Clear all the faces
        /// </summary>
        public void ClearAllFaces()
        {
            _faces.Clear();
        }

        /// <summary>
        /// Get all the faces
        /// </summary>
        /// <returns></returns>
        public List<VisualCubeFace> GetFaces()
        {
            return _faces;
        }

        #endregion

        #region Turn cube & face methods

        /// <summary>
        /// Indicates if the movement is clockwise or counter-clockwise to the face.
        /// </summary>
        /// <param name="faceType">Type of the face</param>
        /// <param name="coord">Coordinate of the movement</param>
        /// <returns>Returns true if the movement is clockwise. Otherwise, false</returns>
        private bool IsClockWise(CubeFaceType faceType, Coordinate coord)
        {
            bool _isClockwise = false;
            switch (faceType)
            {
                case CubeFaceType.U:
                    if (coord.Axis == CoordinateAxis.Z)
                    {
                        if (coord.Value == 90)
                            _isClockwise = true;
                        else if (coord.Value == -90)
                            _isClockwise = false;
                    }
                    break;
                case CubeFaceType.D:
                    if (coord.Axis == CoordinateAxis.Z)
                    {
                        if (coord.Value == -90)
                            _isClockwise = true;
                        else if (coord.Value == +90)
                            _isClockwise = false;
                    }
                    break;
                case CubeFaceType.L:
                    if (coord.Axis == CoordinateAxis.Y)
                    {
                        if (coord.Value == 90)
                            _isClockwise = true;
                        else if (coord.Value == -90)
                            _isClockwise = false;
                    }
                    break;
                case CubeFaceType.R:
                    if (coord.Axis == CoordinateAxis.Y)
                    {
                        if (coord.Value == -90)
                            _isClockwise = true;
                        else if (coord.Value == +90)
                            _isClockwise = false;
                    }
                    break;
                case CubeFaceType.F:
                    if (coord.Axis == CoordinateAxis.X)
                    {
                        if (coord.Value == 90)
                            _isClockwise = true;
                        else if (coord.Value == -90)
                            _isClockwise = false;
                    }
                    break;
                case CubeFaceType.B:
                    if (coord.Axis == CoordinateAxis.X)
                    {
                        if (coord.Value == -90)
                            _isClockwise = true;
                        else if (coord.Value == +90)
                            _isClockwise = false;
                    }
                    break;
            }
            return _isClockwise;
        }

        /// <summary>
        /// Get the coordinates of the movement based on the face origins
        /// </summary>
        /// <param name="fOriging">FaceType origins of the movement</param>
        /// <param name="fDestiny">FaceType destiny</param>
        /// <returns>Returns the coordinate for the new movement</returns>
        private Coordinate GetVariationMovement(CubeFaceType fOriging, CubeFaceType fDestiny)
        {
            int fOr = fOriging.GetHashCode();
            int fDes = fDestiny.GetHashCode();
            return default_moves[fOr, fDes];
        }

        #region Rotate Face Methods

        /// <summary>
        /// Turn the face based on coordinates
        /// </summary>
        /// <param name="face">The face to be turned</param>
        /// <param name="coord">The coordinates</param>
        /// <returns>Return the new face, after the turn.</returns>
        private CubeFaceType RotateFace(CubeFaceType face, Coordinate coord)
        {
            CubeFaceType newFace = CubeFaceType.U;
            switch (face)
            {
                case CubeFaceType.U:
                    newFace = RotateUFace(coord);
                    break;
                case CubeFaceType.D:
                    newFace = RotateDFace(coord);
                    break;
                case CubeFaceType.L:
                    newFace = RotateLFace(coord);
                    break;
                case CubeFaceType.R:
                    newFace = RotateRFace(coord);
                    break;
                case CubeFaceType.F:
                    newFace = RotateFFace(coord);
                    break;
                case CubeFaceType.B:
                    newFace = RotateBFace(coord);
                    break;
            }
            return newFace;
        }

        /// <summary>
        /// Turns the U face according with the coordinates
        /// </summary>
        /// <param name="coord">Coordinates to base the move.</param>
        /// <returns>Returns new face</returns>
        private CubeFaceType RotateUFace(Coordinate coord)
        {
            CubeFaceType faceReturn = CubeFaceType.U;
            if (coord.Value != 0)
            {
                switch (coord.Axis)
                {
                    case CoordinateAxis.X:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.R;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.L;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.D;
                        }
                        break;
                    case CoordinateAxis.Y:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.F;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.B;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.D;
                        }
                        break;
                    case CoordinateAxis.Z:
                        //This face is not affected by the Z axis
                        break;
                    default:
                        break;
                }
            }

            return faceReturn;
        }

        /// <summary>
        /// Turns the D face according with the coordinates
        /// </summary>
        /// <param name="coord">Coordinates to base the move.</param>
        /// <returns>Returns new face</returns>
        private CubeFaceType RotateDFace(Coordinate coord)
        {
            CubeFaceType faceReturn = CubeFaceType.D;
            if (coord.Value != 0)
            {
                switch (coord.Axis)
                {
                    case CoordinateAxis.X:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.L;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.R;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.U;
                        }
                        break;
                    case CoordinateAxis.Y:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.B;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.F;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.U;
                        }
                        break;
                    case CoordinateAxis.Z:
                        //This face is not affected by the Z axis
                        break;
                    default:
                        break;
                }
            }

            return faceReturn;
        }

        /// <summary>
        /// Turns the L face according with the coordinates
        /// </summary>
        /// <param name="coord">Coordinates to base the move.</param>
        /// <returns>Returns new face</returns>
        private CubeFaceType RotateLFace(Coordinate coord)
        {
            CubeFaceType faceReturn = CubeFaceType.L;
            if (coord.Value != 0)
            {
                switch (coord.Axis)
                {
                    case CoordinateAxis.X:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.U;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.D;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.R;
                        }
                        break;
                    case CoordinateAxis.Y:
                        //This face is not affected to the Y axis
                        break;
                    case CoordinateAxis.Z:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.B;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.F;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.R;
                        }
                        break;
                    default:
                        break;
                }
            }

            return faceReturn;
        }

        /// <summary>
        /// Turns the R face according with the coordinates
        /// </summary>
        /// <param name="coord">Coordinates to base the move.</param>
        /// <returns>Returns new face</returns>
        private CubeFaceType RotateRFace(Coordinate coord)
        {
            CubeFaceType faceReturn = CubeFaceType.R;
            if (coord.Value != 0)
            {
                switch (coord.Axis)
                {
                    case CoordinateAxis.X:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.D;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.U;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.L;
                        }
                        break;
                    case CoordinateAxis.Y:
                        //This face is not affected by the Y axis
                        break;
                    case CoordinateAxis.Z:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.F;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.B;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.L;
                        }
                        break;
                    default:
                        break;
                }
            }

            return faceReturn;
        }

        /// <summary>
        /// Turns the F face according with the coordinates
        /// </summary>
        /// <param name="coord">Coordinates to base the move.</param>
        /// <returns>Returns new face</returns>
        private CubeFaceType RotateFFace(Coordinate coord)
        {
            CubeFaceType faceReturn = CubeFaceType.F;
            if (coord.Value != 0)
            {
                switch (coord.Axis)
                {
                    case CoordinateAxis.X:
                        //This face is not affected by X axis
                        break;
                    case CoordinateAxis.Y:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.D;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.U;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.B;
                        }
                        break;
                    case CoordinateAxis.Z:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.L;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.R;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.B;
                        }
                        break;
                }
            }

            return faceReturn;
        }

        /// <summary>
        /// Turns the F face according with the coordinates
        /// </summary>
        /// <param name="coord">Coordinates to base the move.</param>
        /// <returns>Returns new face</returns>
        private CubeFaceType RotateBFace(Coordinate coord)
        {
            CubeFaceType faceReturn = CubeFaceType.B;
            if (coord.Value != 0)
            {
                switch (coord.Axis)
                {
                    case CoordinateAxis.X:
                        //This face is not affected by X axis
                        break;
                    case CoordinateAxis.Y:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.U;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.D;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.F;
                        }
                        break;
                    case CoordinateAxis.Z:
                        if (coord.Value == 90)
                        {
                            faceReturn = CubeFaceType.R;
                        }
                        else if (coord.Value == -90)
                        {
                            faceReturn = CubeFaceType.L;
                        }
                        else if (coord.Value == 180)
                        {
                            faceReturn = CubeFaceType.F;
                        }
                        break;
                    default:
                        break;
                }
            }

            return faceReturn;
        }

        #endregion

        #region Change Blocks Position Methods

        /// <summary>
        /// Changes the position of all cubeblocks. CHECKS if the coordinate value is 0.
        /// </summary>
        /// <param name="faceType">Type of the face</param>
        /// <param name="blockMatrix">The blockmatrix of the face</param>
        /// <param name="coord">The coordinate of the movement</param>
        private void ChangeBlocksPosition(CubeFaceType faceType, List<VisualCubeBlock> blockMatrix, Coordinate coord)
        {
            if (coord.Value != 0)
            {
                switch (faceType)
                {
                    case CubeFaceType.U:
                    case CubeFaceType.D:
                        ChangeUDBlockPosition(faceType, blockMatrix, coord);
                        break;
                    case CubeFaceType.L:
                    case CubeFaceType.R:
                        ChangeLRBlockPosition(faceType, blockMatrix, coord);
                        break;
                    case CubeFaceType.F:
                    case CubeFaceType.B:
                        ChangeFBBlockPosition(faceType, blockMatrix, coord);
                        break;
                }
            }
        }

        /// <summary>
        /// Change the position of the blocks from U or D face. DOES NOT CHECK if the value of coordinate is 0.
        /// </summary>
        /// <param name="faceType">The facetype wich the blockmatrix belong</param>
        /// <param name="blockMatrix">The block matrix to change positions</param>
        /// <param name="coord">The coordinate of the movement</param>
        private void ChangeUDBlockPosition(CubeFaceType faceType, List<VisualCubeBlock> blockMatrix, Coordinate coord)
        {
            switch (coord.Axis)
            {
                case CoordinateAxis.X:
                    if (coord.Value == 90)
                        RotateBlockMatrix(blockMatrix, true);
                    else if (coord.Value == -90)
                        RotateBlockMatrix(blockMatrix, false);
                    else
                    {
                        RotateBlockMatrix(blockMatrix, false);
                        RotateBlockMatrix(blockMatrix, false);
                    }
                    break;
                case CoordinateAxis.Y:
                    if (faceType == CubeFaceType.U && coord.Value == -90)
                    {
                        RotateBlockMatrix(blockMatrix, true);
                        RotateBlockMatrix(blockMatrix, true);
                    }
                    else if (faceType == CubeFaceType.D && coord.Value == +90)
                    {
                        RotateBlockMatrix(blockMatrix, true);
                        RotateBlockMatrix(blockMatrix, true);
                    }
                    break;
                case CoordinateAxis.Z:
                    if (coord.Value != 180)
                        RotateBlockMatrix(blockMatrix, IsClockWise(faceType, coord));
                    else
                    {
                        RotateBlockMatrix(blockMatrix, true);
                        RotateBlockMatrix(blockMatrix, true);
                    }
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// Change the position of the blocks from L or R face. DOES NOT CHECK if the value of coordinate is 0.
        /// </summary>
        /// <param name="faceType">The facetype wich the blockmatrix belong</param>
        /// <param name="blockMatrix">The block matrix to change positions</param>
        /// <param name="coord">The coordinate of the movement</param>
        private void ChangeLRBlockPosition(CubeFaceType faceType, List<VisualCubeBlock> blockMatrix, Coordinate coord)
        {
            switch (coord.Axis)
            {
                case CoordinateAxis.X:
                    if (coord.Value == 90)
                        RotateBlockMatrix(blockMatrix, true);
                    else if (coord.Value == -90)
                        RotateBlockMatrix(blockMatrix, false);
                    else
                    {
                        RotateBlockMatrix(blockMatrix, false);
                        RotateBlockMatrix(blockMatrix, false);
                    }
                    break;
                case CoordinateAxis.Y:
                    if (coord.Value != 180)
                        RotateBlockMatrix(blockMatrix, IsClockWise(faceType, coord));
                    else
                    {
                        RotateBlockMatrix(blockMatrix, false);
                        RotateBlockMatrix(blockMatrix, false);
                    }
                    break;
                case CoordinateAxis.Z:
                    //It is not affected
                    break;
            }
        }

        /// <summary>
        /// Change the block matrix positions of the F and the B faces.DOES NOT CHECK if the value of coordinate is 0.
        /// </summary>
        /// <param name="faceType">The facetype wich the blockmatrix belong</param>
        /// <param name="blockMatrix">The block matrix to change positions</param>
        /// <param name="coord">The coordinate of the movement</param>
        private void ChangeFBBlockPosition(CubeFaceType faceType, List<VisualCubeBlock> blockMatrix, Coordinate coord)
        {
            switch (coord.Axis)
            {
                case CoordinateAxis.X:
                    if (coord.Value == 90)
                        RotateBlockMatrix(blockMatrix, (faceType == CubeFaceType.F));
                    else if (coord.Value == -90)
                        RotateBlockMatrix(blockMatrix, (faceType != CubeFaceType.F));
                    else
                    {
                        RotateBlockMatrix(blockMatrix, true);
                        RotateBlockMatrix(blockMatrix, true);
                    }
                    break;
                case CoordinateAxis.Y:
                    if (faceType == CubeFaceType.B)
                    {
                        RotateBlockMatrix(blockMatrix, true);
                        RotateBlockMatrix(blockMatrix, true);
                    }
                    else if (coord.Value == 180)
                    {
                        RotateBlockMatrix(blockMatrix, true);
                        RotateBlockMatrix(blockMatrix, true);
                    }
                    break;
                case CoordinateAxis.Z:
                    //No changes
                    break;
            }
        }

        /// <summary>
        /// Rotates the block matrix face.
        /// </summary>
        /// <param name="blockMatrix">The block matrix to rotate</param>
        /// <param name="clockWise">If true, performs clockwisely. Otherwise, performs counter-clockwisely</param>
        private void RotateBlockMatrix(List<VisualCubeBlock> blockMatrix, bool clockWise)
        {
            foreach (VisualCubeBlock item in blockMatrix)
            {
                int index = (int)item.Square;
                if (!clockWise)
                {
                    index = 8 - index;
                }
                item.Square = clkwse_blkmtrix[index];
            }
        }

        #endregion

        #region Turn Face Methods

        /// <summary>
        /// Turns the U or D face
        /// </summary>
        /// <param name="faceType">The type of the face</param>
        /// <param name="coord">Coordinate of the movement</param>
        private void TurnUDFace(CubeFaceType faceType, Coordinate coord)
        {
            if (coord.Value != 0)
            {
                if (coord.Axis != CoordinateAxis.Z)
                {
                    //If not Z, it is impossible to turn only the U/D face. So, it turns the whole cube
                    TurnCube(coord);
                }
                else
                {
                    //Changes the position of the blocks in the face
                    ChangeUDBlockPosition(faceType, this[faceType].GetBlocks(), coord);
                    List<VisualCubeBlock> next_Blocks = new List<VisualCubeBlock>();
                    List<VisualCubeBlock> block_toChange = new List<VisualCubeBlock>();
                    List<VisualCubeBlock> search_blocks = new List<VisualCubeBlock>();
                    CubeFaceType[] face_order = new CubeFaceType[] { CubeFaceType.F, CubeFaceType.L, CubeFaceType.B, CubeFaceType.R };
                    bool clockwise = IsClockWise(CubeFaceType.U, coord);
                    int index;
                    int post_index = 0;
                    int incremento = (coord.Value != 180) ? 1 : 2;
                    int limit = (coord.Value != 180) ? 4 : 2;
                    for (int i = 0; i < limit; i++)
                    {
                        //Determine the current index and the next index
                        index = i;
                        post_index = index + incremento;
                        if (!clockwise && coord.Value != 180)
                        {
                            index = 3 - index;
                            post_index = index - 1;
                        }
                        //Ajust last post_index
                        if (post_index == -1)
                            post_index = 3;
                        else if (post_index == 4)
                            post_index = 0;
                        //Gets the current face and the next face
                        VisualCubeFace currentFace = this[face_order[index]];
                        VisualCubeFace nextFace = this[face_order[post_index]];
                        //Save the next blocks
                        search_blocks = (faceType == CubeFaceType.U) ? nextFace.GetUpBlocks() : nextFace.GetDownBlocks();
                        next_Blocks.Clear();
                        foreach (VisualCubeBlock item in search_blocks)
                        {
                            next_Blocks.Add(item.Clone());
                        }
                        //load the current blocks, if necessary, and adds to the next face
                        if (block_toChange.Count == 0)
                        {
                            search_blocks = (faceType == CubeFaceType.U) ? currentFace.GetUpBlocks() : currentFace.GetDownBlocks();
                            foreach (VisualCubeBlock item in search_blocks)
                            {
                                VisualCubeBlock toChange = item.Clone();
                                block_toChange.Add(toChange);
                            }
                        }
                        //Changes the position of the blocks turned
                        ChangeBlocksPosition(face_order[index], block_toChange, coord);

                        //Adds to the face
                        foreach (VisualCubeBlock item in block_toChange)
                        {
                            nextFace.AddBlock(item.Clone(), false);
                        }

                        //Redo the cycle, copying the temp_blocks to block_toChange;
                        block_toChange.Clear();
                        if (coord.Value != 180)
                        {
                            foreach (VisualCubeBlock item in next_Blocks)
                            {
                                block_toChange.Add(item.Clone());
                            }
                        }
                        else
                        {
                            ChangeBlocksPosition(face_order[post_index], next_Blocks, coord);
                            foreach (VisualCubeBlock item in next_Blocks)
                            {
                                currentFace.AddBlock(item.Clone(), false);
                            }
                        }
                    }
                    if (coord.Value != 180)
                        ChangeBlocksPosition(face_order[post_index], block_toChange, coord);
                }
            }
        }

        /// <summary>
        /// Turns the L or R face
        /// </summary>
        /// <param name="faceType">The type of the face</param>
        /// <param name="coord">Coordinate of the movement</param>
        private void TurnLFace(CubeFaceType faceType, Coordinate coord)
        {
            if (coord.Value != 0)
            {
                if (coord.Axis != CoordinateAxis.Y)
                {
                    //If not Y, it is impossible to turn only the L/R face. So, it turns the whole cube
                    TurnCube(coord);
                }
                else
                {
                    //Changes the position of the blocks in the face
                    ChangeLRBlockPosition(faceType, this[faceType].GetBlocks(), coord);

                    List<VisualCubeBlock> next_Blocks = new List<VisualCubeBlock>();
                    List<VisualCubeBlock> block_toChange = new List<VisualCubeBlock>();
                    List<VisualCubeBlock> search_blocks = new List<VisualCubeBlock>();
                    CubeFaceType[] face_order = new CubeFaceType[] { CubeFaceType.F, CubeFaceType.D, CubeFaceType.B, CubeFaceType.U };

                    bool clockwise = IsClockWise(CubeFaceType.L, coord);
                    int index;
                    int post_index = 0;
                    int incremento = (coord.Value != 180) ? 1 : 2;
                    int limit = (coord.Value != 180) ? 4 : 2;
                    for (int i = 0; i < limit; i++)
                    {
                        //Determine the current index and the next index
                        index = i;
                        post_index = index + incremento;
                        if (!clockwise && coord.Value != 180)
                        {
                            index = 3 - index;
                            post_index = index - 1;
                        }
                        //Ajust last post_index
                        if (post_index == -1)
                            post_index = 3;
                        else if (post_index == 4)
                            post_index = 0;
                        //Gets the current face and the next face
                        VisualCubeFace currentFace = this[face_order[index]];
                        VisualCubeFace nextFace = this[face_order[post_index]];
                        //Save the next blocks
                        if (faceType == CubeFaceType.L)
                        {
                            search_blocks = (face_order[post_index] == CubeFaceType.B) ? nextFace.GetRightBlocks() : nextFace.GetLeftBlocks();
                        }
                        else
                        {
                            search_blocks = (face_order[post_index] != CubeFaceType.B) ? nextFace.GetRightBlocks() : nextFace.GetLeftBlocks();
                        }
                        next_Blocks.Clear();
                        foreach (VisualCubeBlock item in search_blocks)
                        {
                            next_Blocks.Add(item.Clone());
                        }
                        //load the current blocks, if necessary
                        if (block_toChange.Count == 0)
                        {
                            if (faceType == CubeFaceType.L)
                            {
                                search_blocks = (face_order[index] == CubeFaceType.B) ? currentFace.GetRightBlocks() : currentFace.GetLeftBlocks();
                            }
                            else
                            {
                                search_blocks = (face_order[index] != CubeFaceType.B) ? currentFace.GetRightBlocks() : currentFace.GetLeftBlocks();
                            }
                            foreach (VisualCubeBlock item in search_blocks)
                            {
                                VisualCubeBlock toChange = item.Clone();
                                block_toChange.Add(toChange);
                            }
                        }
                        //Changes the position of the blocks turned
                        ChangeBlocksPosition(face_order[index], block_toChange, coord);

                        //Adds to the face
                        foreach (VisualCubeBlock item in block_toChange)
                        {
                            nextFace.AddBlock(item.Clone(), false);
                        }

                        //Redo the cycle, copying the temp_blocks to block_toChange;
                        block_toChange.Clear();
                        if (coord.Value != 180)
                        {
                            foreach (VisualCubeBlock item in next_Blocks)
                            {
                                block_toChange.Add(item.Clone());
                            }
                        }
                        else
                        {
                            ChangeBlocksPosition(face_order[post_index], next_Blocks, coord);
                            foreach (VisualCubeBlock item in next_Blocks)
                            {
                                currentFace.AddBlock(item.Clone(), false);
                            }
                        }
                    }
                    if (coord.Value != 180)
                        ChangeBlocksPosition(face_order[post_index], block_toChange, coord);

                }
            }
        }

        /// <summary>
        /// Turns the F or B face
        /// </summary>
        /// <param name="faceType">The type of the face</param>
        /// <param name="coord">Coordinate of the movement</param>
        private void TurnFBFace(CubeFaceType faceType, Coordinate coord)
        {
            if (coord.Value != 0)
            {
                if (coord.Axis != CoordinateAxis.X)
                {
                    //If not X, it is impossible to turn only the F/B face. So, it turns the whole cube
                    TurnCube(coord);
                }
                else
                {
                    //Changes the position of the blocks in the face
                    ChangeFBBlockPosition(faceType, this[faceType].GetBlocks(), coord);
                    List<VisualCubeBlock> next_Blocks = new List<VisualCubeBlock>();
                    List<VisualCubeBlock> block_toChange = new List<VisualCubeBlock>();
                    List<VisualCubeBlock> search_blocks = new List<VisualCubeBlock>();
                    CubeFaceType[] face_order = new CubeFaceType[] { CubeFaceType.U, CubeFaceType.R, CubeFaceType.D, CubeFaceType.L };
                    bool clockwise = IsClockWise(CubeFaceType.F, coord);
                    int index;
                    int post_index = 0;
                    int incremento = (coord.Value != 180) ? 1 : 2;
                    int limit = (coord.Value != 180) ? 4 : 2;
                    for (int i = 0; i < limit; i++)
                    {
                        //Determine the current index and the next index
                        index = i;
                        post_index = index + incremento;
                        if (!clockwise && coord.Value != 180)
                        {
                            index = 3 - index;
                            post_index = index - 1;
                        }
                        //Ajust last post_index
                        if (post_index == -1)
                            post_index = 3;
                        else if (post_index == 4)
                            post_index = 0;
                        //Gets the current face and the next face
                        VisualCubeFace currentFace = this[face_order[index]];
                        VisualCubeFace nextFace = this[face_order[post_index]];
                        //Save the next blocks
                        switch (face_order[post_index])
                        {
                            case CubeFaceType.U:
                                search_blocks = (faceType == CubeFaceType.F) ? nextFace.GetDownBlocks() : nextFace.GetUpBlocks();
                                break;
                            case CubeFaceType.D:
                                search_blocks = (faceType == CubeFaceType.F) ? nextFace.GetUpBlocks() : nextFace.GetDownBlocks();
                                break;
                            case CubeFaceType.L:
                                search_blocks = (faceType == CubeFaceType.F) ? nextFace.GetRightBlocks() : nextFace.GetLeftBlocks();
                                break;
                            case CubeFaceType.R:
                                search_blocks = (faceType == CubeFaceType.F) ? nextFace.GetLeftBlocks() : nextFace.GetRightBlocks();
                                break;
                        }
                        next_Blocks.Clear();
                        foreach (VisualCubeBlock item in search_blocks)
                        {
                            next_Blocks.Add(item.Clone());
                        }
                        //load the current blocks, if necessary, and adds to the next face
                        if (block_toChange.Count == 0)
                        {
                            //Save the next blocks
                            switch (face_order[index])
                            {
                                case CubeFaceType.U:
                                    search_blocks = (faceType == CubeFaceType.F) ? currentFace.GetDownBlocks() : currentFace.GetUpBlocks();
                                    break;
                                case CubeFaceType.D:
                                    search_blocks = (faceType == CubeFaceType.F) ? currentFace.GetUpBlocks() : currentFace.GetDownBlocks();
                                    break;
                                case CubeFaceType.L:
                                    search_blocks = (faceType == CubeFaceType.F) ? currentFace.GetRightBlocks() : currentFace.GetLeftBlocks();
                                    break;
                                case CubeFaceType.R:
                                    search_blocks = (faceType == CubeFaceType.F) ? currentFace.GetLeftBlocks() : currentFace.GetRightBlocks();
                                    break;
                            }
                            foreach (VisualCubeBlock item in search_blocks)
                            {
                                VisualCubeBlock toChange = item.Clone();
                                block_toChange.Add(toChange);
                            }
                        }
                        //Changes the position of the blocks turned
                        ChangeBlocksPosition(face_order[index], block_toChange, coord);

                        //Adds to the next face
                        foreach (VisualCubeBlock item in block_toChange)
                        {
                            nextFace.AddBlock(item, false);
                        }

                        //Redo the cycle, copying the temp_blocks to block_toChange;
                        block_toChange.Clear();
                        if (coord.Value != 180)
                        {
                            foreach (VisualCubeBlock item in next_Blocks)
                            {
                                block_toChange.Add(item.Clone());
                            }
                        }
                        else
                        {
                            ChangeBlocksPosition(face_order[post_index], next_Blocks, coord);
                            foreach (VisualCubeBlock item in next_Blocks)
                            {
                                currentFace.AddBlock(item.Clone(), false);
                            }
                        }
                    }
                    if (coord.Value != 180)
                        ChangeBlocksPosition(face_order[post_index], block_toChange, coord);
                }
            }
        }

        #endregion

        /// <summary>
        /// Turns, if it is necessary, the cube to the face become the desired type.
        /// </summary>
        /// <param name="f">Face to turn</param>
        /// <param name="desiredType">Desired type for the face</param>
        public void TurnCube(VisualCubeFace f, CubeFaceType desiredType)
        {
            if (f.FaceType != desiredType)
            {
                Coordinate coord = GetVariationMovement(f.FaceType, desiredType);
                TurnCube(coord);
            }
        }

        /// <summary>
        /// Turns, if it is necessary, the cube to the face become the desired type.
        /// </summary>
        /// <param name="coord">The coordinate to turn the cube.</param>
        public void TurnCube(Coordinate coord)
        {
            if (coord.Value != 0)
            {
                foreach (VisualCubeFace face in this._faces)
                {
                    ChangeBlocksPosition(face.FaceType, face.GetBlocks(), coord);
                    face.FaceType = RotateFace(face.FaceType, coord);
                }
            }
        }

        /// <summary>
        /// Turns the especific face
        /// </summary>
        /// <param name="faceType">The type of the face</param>
        /// <param name="coord">The coordinate of the face</param>
        public void TurnFace(CubeFaceType faceType, Coordinate coord)
        {
            switch (faceType)
            {
                case CubeFaceType.U:
                case CubeFaceType.D:
                    TurnUDFace(faceType, coord);
                    break;
                case CubeFaceType.L:
                case CubeFaceType.R:
                    TurnLFace(faceType, coord);
                    break;
                case CubeFaceType.F:
                case CubeFaceType.B:
                    TurnFBFace(faceType, coord);
                    break;
            }
        }

        #endregion

        #endregion

        /// <summary>
        /// Returns the position of the color face in the cube (U, D, F, B, L, R).
        /// </summary>
        /// <param name="color">Color of the face to look for</param>
        public CubeFaceType GetFacePositionByColor(CubeFaceColor color)
        {
            foreach (VisualCubeFace face in _faces)
            {
                if (face.FaceColor.Equals(color))
                    return face.FaceType;
            }
            return CubeFaceType.U;
        }
    }
}

