using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace RubikCube
{
    /// <summary>
    /// A face of a Cube
    /// </summary>
    [Serializable]
    public class VisualCubeFace : IDisposable
    {
        #region Fields

        /// <summary>
        /// The list to hold the blocks
        /// </summary>
        private List<VisualCubeBlock> _blocks = new List<VisualCubeBlock>();

        #endregion

        #region Props

        /// <summary>
        /// The face type in the Cube
        /// </summary>
        public CubeFaceType FaceType { get; set; }

        /// <summary>
        /// The color of the face
        /// </summary>
        public CubeFaceColor FaceColor { get; set; }

        public VisualCubeBlock this[CubeFaceletType type]
        {
            get
            {
                VisualCubeBlock blockRet = null;
                foreach (VisualCubeBlock item in _blocks)
                {
                    if (item.Square == type)
                    {
                        blockRet = item;
                        break;
                    }
                }
                if (blockRet != null)
                    return blockRet;
                else
                    throw new IndexOutOfRangeException();
            }
            set
            {
                int index = -1;
                for (int i = 0; i < _blocks.Count; i++)
                {
                    if (_blocks[i].Square == type)
                    {
                        index = i;
                        break;
                    }
                }
                if (index >= 0)
                    _blocks[index] = value;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Adds or edit the block in the list.
        /// </summary>
        /// <param name="newBlock">The block to add/edit</param>
        /// <param name="beforeBlockSort">If true, compares the position in the image to know if the blocks already exists. Otherwise, compare the Square property</param>
        public void AddBlock(VisualCubeBlock newBlock, bool beforeBlockSort)
        {
            int foundIndex = -1;
            for (int i = 0; i < _blocks.Count; i++)
            {
                if (beforeBlockSort)
                {
                    if (newBlock.Rectangle.Equals(_blocks[i].Rectangle))
                    {
                        foundIndex = i;
                        break;
                    }
                }
                else
                {
                    if (newBlock.Square == _blocks[i].Square)
                    {
                        foundIndex = i;
                        break;
                    }
                }
            }
            if (foundIndex == -1)
                _blocks.Add(newBlock);
            else
            {
                _blocks[foundIndex].Color = newBlock.Color;
            }
            if (newBlock.IsCenter())
                this.FaceColor = newBlock.Color;
        }

        /// <summary>
        /// Clear all the blocks in the list
        /// </summary>
        public void ClearBlocks()
        {
            _blocks.Clear();
        }

        /// <summary>
        /// Get the blocks count
        /// </summary>
        /// <returns>Return the blocks count</returns>
        public int GetBlocksCount()
        {
            return _blocks.Count;
        }

        /// <summary>
        /// Get the upside blocks of the face
        /// </summary>
        /// <returns>Returns a list of up blocks</returns>
        public List<VisualCubeBlock> GetUpBlocks()
        {
            List<VisualCubeBlock> upBlocks = new List<VisualCubeBlock>();
            foreach (VisualCubeBlock item in _blocks)
            {
                if (item.IsUpBlock())
                {
                    upBlocks.Add(item);
                    if (upBlocks.Count == 3)
                        break;
                }
            }
            return upBlocks;
        }

        /// <summary>
        /// Get the downside blocks of the face
        /// </summary>
        /// <returns>Returns a list of down blocks</returns>
        public List<VisualCubeBlock> GetDownBlocks()
        {
            List<VisualCubeBlock> downBlocks = new List<VisualCubeBlock>();
            foreach (VisualCubeBlock item in _blocks)
            {
                if (item.IsDownBlock())
                {
                    downBlocks.Add(item);
                    if (downBlocks.Count == 3)
                        break;
                }
            }
            return downBlocks;
        }

        /// <summary>
        /// Get the leftside blocks of the face
        /// </summary>
        /// <returns>Returns a list of left blocks</returns>
        public List<VisualCubeBlock> GetLeftBlocks()
        {
            List<VisualCubeBlock> lftBlocks = new List<VisualCubeBlock>();
            foreach (VisualCubeBlock item in _blocks)
            {
                if (item.IsLeftBlock())
                {
                    lftBlocks.Add(item);
                    if (lftBlocks.Count == 3)
                        break;
                }
            }
            return lftBlocks;
        }

        /// <summary>
        /// Get the rightside blocks of the face
        /// </summary>
        /// <returns>Returns a list of right blocks</returns>
        public List<VisualCubeBlock> GetRightBlocks()
        {
            List<VisualCubeBlock> rgtBlocks = new List<VisualCubeBlock>();
            foreach (VisualCubeBlock item in _blocks)
            {
                if (item.IsRightBlock())
                {
                    rgtBlocks.Add(item);
                    if (rgtBlocks.Count == 3)
                        break;
                }
            }
            return rgtBlocks;
        }

        /// <summary>
        /// Get a list of the blocks
        /// </summary>
        /// <returns>Return the list of the blocks</returns>
        public List<VisualCubeBlock> GetBlocks()
        {
            return _blocks;
        }

        /// <summary>
        /// Sort the list of blocks, defining their positions in the face based on X and Y coordinates.
        /// </summary>
        /// <returns>Return true if the sort was completed. Otherwise, false</returns>
        public bool SortBlockList()
        {
            if (this._blocks.Count == 9)
            {
                _blocks.Sort(new Comparison<VisualCubeBlock>(SortBlockListByY));
                string nextLayer = "Up";
                List<int> subSet = new List<int>();
                for (int i = 0; i < _blocks.Count; i += 3)
                {
                    subSet.Clear();
                    subSet.Add(i);
                    subSet.Add(i + 1);
                    subSet.Add(i + 2);
                    nextLayer = DefineLayerBlocksPositions(subSet, nextLayer);
                }
                this.FaceColor = this[CubeFaceletType.Center].Color;
                return true;
            }
            return false;
        }

        /// <summary>
        /// Clones the object
        /// </summary>
        /// <returns></returns>
        public VisualCubeFace Clone()
        {
            MemoryStream ms = new MemoryStream();
            BinaryFormatter bf = new BinaryFormatter();

            bf.Serialize(ms, this);

            ms.Position = 0;
            object obj = bf.Deserialize(ms);
            ms.Close();

            return obj as VisualCubeFace;
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Sort method delegate to compare the Y coordinates of blocks
        /// </summary>
        /// <param name="b1">The first block to compare.</param>
        /// <param name="b2">The second block to compare.</param>
        /// <returns>Returns -1 if the first Y is lower thant the second. 1 if the second Y is lower than the first. 0 if they are equal</returns>
        private int SortBlockListByY(VisualCubeBlock b1, VisualCubeBlock b2)
        {
            int retorno = 0;
            if (b1.Rectangle.Y < b2.Rectangle.Y)
                retorno = -1;
            else if (b1.Rectangle.Y > b2.Rectangle.Y)
                retorno = 1;
            return retorno;
        }

        /// <summary>
        /// Sort method delegate to compare the X coordinates of blocks, based on the index
        /// </summary>
        /// <param name="b1">The first index to compare</param>
        /// <param name="b2">The second index to compare</param>
        /// <returns>Returns -1 if the first X is lower thant the second. 1 if the second X is lower than the first. 0 if they are equal</returns>
        private int SortBlockListByX(int b1, int b2)
        {
            int retorno = 0;
            if (_blocks[b1].Rectangle.X < _blocks[b2].Rectangle.X)
                retorno = -1;
            else if (_blocks[b1].Rectangle.X > _blocks[b2].Rectangle.X)
                retorno = 1;
            return retorno;
        }

        /// <summary>
        /// Define the position for blocks of a layer based on the list of indexers, comparing X coordinate.
        /// </summary>
        /// <param name="index">Ther list of indexes of the blocks in the layer</param>
        /// <param name="layer">The name of the layer</param>
        /// <returns>Returns the next layer name</returns>
        private string DefineLayerBlocksPositions(List<int> index, string layer)
        {
            string nextLayer = string.Empty;
            index.Sort(new Comparison<int>(SortBlockListByX));

            _blocks[index[0]].Square = (CubeFaceletType)Enum.Parse(typeof(CubeFaceletType), string.Format("{0}Left", layer));
            if (layer.Equals("Mid"))
                _blocks[index[1]].Square = (CubeFaceletType)Enum.Parse(typeof(CubeFaceletType), "Center");
            else
                _blocks[index[1]].Square = (CubeFaceletType)Enum.Parse(typeof(CubeFaceletType), string.Format("{0}Mid", layer));
            _blocks[index[2]].Square = (CubeFaceletType)Enum.Parse(typeof(CubeFaceletType), string.Format("{0}Right", layer));

            if (layer.Equals("Mid"))
                nextLayer = "Down";
            else
                nextLayer = "Mid";
            return nextLayer;
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
