using System;
using System.Collections.Generic;
using System.Text;
using RubikCube;

namespace CubeSolver
{
    public class CubeSolver
    {
        private List<Algorithm> algorithms = new List<Algorithm>();

        /// <summary>
        /// Get a list of all corners that has the same side of the face.
        /// </summary>
        /// <param name="fSearch">Face to search</param>
        /// <returns>Returns a list with all the corners</returns>
        private List<VisualCubeBlock> GetCornersFromSameSide(VisualCubeFace fSearch)
        {
            List<VisualCubeBlock> lsBlocks = new List<VisualCubeBlock>();
            foreach (VisualCubeBlock item in fSearch.GetBlocks())
            {
                if (item.Color.Equals(fSearch.FaceColor) && item.IsCorner())
                    lsBlocks.Add(item);
            }
            return lsBlocks;
        }

        /// <summary>
        /// Gets the start face to organize the corners
        /// </summary>
        /// <param name="c">Cube to search</param>
        /// <param name="blocks">Returns all the blocks with same side of the face</param>
        /// <returns>Returns the selected CubeFace.</returns>
        private VisualCubeFace GetStartFace(VisualCube c, out List<VisualCubeBlock> blocks)
        {
            VisualCubeFace selFace = new VisualCubeFace();
            blocks = new List<VisualCubeBlock>();
            foreach (VisualCubeFace item in c.GetFaces())
            {
                blocks = GetCornersFromSameSide(item);
                if (blocks.Count > 0)
                {
                    //TODO: Select best face to get the corner.
                    selFace = item;
                    break;
                }

            }
            return selFace;
        }

        private void SetFacePosition(VisualCube c, VisualCubeFace fToTurn, CubeFaceType desiredType)
        {
            if (fToTurn.FaceType != desiredType)
            {
                c.TurnCube(fToTurn, desiredType);
            }
        }

        /// <summary>
        /// Solves the first corners of the cube 
        /// </summary>
        /// <param name="cSolve">Cube to solve</param>
        private void SolveFirstCorners(VisualCube cSolve)
        {
            List<VisualCubeBlock> blocks;
            VisualCubeFace startFace = GetStartFace(cSolve, out blocks);
        }
    }
}
