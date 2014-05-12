using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    public class RotateCubeMovement : Movement
    {
        /// <summary>
        /// Axis to rotate the cube.
        /// </summary>
        public CoordinateAxis Axis { get; set; }

        public override String toString()
        {
            return "--> Rotate Cube Movement - Axis: [" + Axis.ToString() + "] Type: [" + Type.ToString() + "]";
        }
    }
}
