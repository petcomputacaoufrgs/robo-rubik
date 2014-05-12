using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    /// <summary>
    /// Coordinates for movement actions
    /// </summary>
    public class Coordinate
    {
        #region Props

        /// <summary>
        /// The value of the coordinate
        /// </summary>
        public int Value { get; set; }

        /// <summary>
        /// The correspondent axis
        /// </summary>
        public CoordinateAxis Axis { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Coordinates for movement actions
        /// </summary>
        /// <param name="axis">The correspondent axis</param>
        /// <param name="value">The value of the coordinate</param>
        public Coordinate(CoordinateAxis axis, int value)
        {
            this.Value = value;
            this.Axis = axis;
        }

        #endregion
    }
}
