using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace RubikCube
{
    /// <summary>
    /// Represents a square in the face of the cube
    /// </summary>
    [Serializable]
    public class CubeBlock : IDisposable
    {
        #region Props

        /// <summary>
        /// Position in the face
        /// </summary>
        public CubeFaceletType Square { get; set; }

        /// <summary>
        /// Rectangle from the image captured
        /// </summary>
        public Rectangle Rectangle { get; set; }

        /// <summary>
        /// Color of the block
        /// </summary>
        public Color Color { get; set; }

        /// <summary>
        /// Color of the first adjacent block of the block. If is a Center block, this is disconsidered.
        /// </summary>
        public Color BlockSideA { get; set; }

        /// <summary>
        /// Color of the second adjacent block of the block. If is a Center or Edge block, this is disconsidered.
        /// </summary>
        public Color BlockSideB { get; set; }

        #endregion

        #region Methods

        /// <summary>
        /// Checks if block is corner
        /// </summary>
        /// <returns>Return true if is corner. Otherwise, false</returns>
        public bool IsCorner()
        {
            return (this.Square == CubeFaceletType.UpLeft || this.Square == CubeFaceletType.UpRight || this.Square == CubeFaceletType.DownLeft || this.Square == CubeFaceletType.DownRight);
        }

        /// <summary>
        /// Checks if block is edge.
        /// </summary>
        /// <returns>Returns true if it is edge. Otherwise, false.</returns>
        public bool IsEdge()
        {
            return (this.Square == CubeFaceletType.UpMid || this.Square == CubeFaceletType.MidLeft || this.Square == CubeFaceletType.MidRight || this.Square == CubeFaceletType.DownMid);
        }

        /// <summary>
        /// Checks if block is center.
        /// </summary>
        /// <returns>Returns true if it is center. Otherwise, false.</returns>
        public bool IsCenter()
        {
            return this.Square == CubeFaceletType.Center;
        }

        /// <summary>
        /// Checks if the block is in the upside of the face
        /// </summary>
        /// <returns>Returns true if it is an up block. Otherwise, false</returns>
        public bool IsUpBlock()
        {
            return (Square == CubeFaceletType.UpLeft || Square == CubeFaceletType.UpMid || Square == CubeFaceletType.UpRight);
        }

        /// <summary>
        /// Checks if the block is in the downside of the face
        /// </summary>
        /// <returns>Returns true if it is a down block. Otherwise, false</returns>
        public bool IsDownBlock()
        {
            return (Square == CubeFaceletType.DownLeft || Square == CubeFaceletType.DownMid || Square == CubeFaceletType.DownRight);
        }

        /// <summary>
        /// Checks if the block is in the leftside of the face
        /// </summary>
        /// <returns>Returns true if it is a left block. Otherwise, false</returns>
        public bool IsLeftBlock()
        {
            return (Square == CubeFaceletType.UpLeft || Square == CubeFaceletType.MidLeft || Square == CubeFaceletType.DownLeft);
        }

        /// <summary>
        /// Checks if the block is in the rightside of the face
        /// </summary>
        /// <returns>Returns true if it is a right block. Otherwise, false</returns>
        public bool IsRightBlock()
        {
            return (Square == CubeFaceletType.UpRight || Square == CubeFaceletType.MidRight || Square == CubeFaceletType.DownRight);
        }

        /// <summary>
        /// Clones the object
        /// </summary>
        /// <returns></returns>
        public CubeBlock Clone()
        {
            MemoryStream ms = new MemoryStream();
            BinaryFormatter bf = new BinaryFormatter();

            bf.Serialize(ms, this);

            ms.Position = 0;
            object obj = bf.Deserialize(ms);
            ms.Close();

            return obj as CubeBlock;
        }

        #endregion

        #region IDisposable Members

        public void Dispose()
        {
            GC.SuppressFinalize(this);
        }

        #endregion
    }
}
