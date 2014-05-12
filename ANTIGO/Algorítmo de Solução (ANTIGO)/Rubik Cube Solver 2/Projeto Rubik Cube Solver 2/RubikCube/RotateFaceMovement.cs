using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    public class RotateFaceMovement : Movement
    {
        /// <summary>
        /// Color of the face to rotate.
        /// </summary>
        public CubeFaceColor Face { get; set; }

        /// <summary>
        /// Position of the face to rotate.
        /// </summary>
        public CubeFaceType PositionFace { get; set; }

        public RotateFaceMovement() { }

        public RotateFaceMovement(CubeFaceColor color, CubeFaceType type)
        {
            Face = color;
            PositionFace = type;
        }

        public override String toString()
        {
            return "Rotate Face Movement - Pos: [" + PositionFace.ToString() + "] Type: [" + Type.ToString() + "] Color: [" + Face.ToString() + "]";
        }
    }
}
