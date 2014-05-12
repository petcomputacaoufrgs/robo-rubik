using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    public class CubeFace
    {
        private List<CubeFacelet> facelets = new List<CubeFacelet>();

        /// <summary>
        /// Facelets of the face
        /// </summary>
        public List<CubeFacelet> Facelets
        {
            get { return facelets; }
            set { facelets = value; }
        }

        private int SortFaceletsDelegate(CubeFacelet f1, CubeFacelet f2)
        {
            int retorno = 0;
            if (f1.Rectangle.Y < f2.Rectangle.Y)
            {
                retorno = -1;
            }
            else if (f1.Rectangle.Y > f2.Rectangle.Y)
            {
                retorno = 1;
            }
            else
            {
                if (f1.Rectangle.X < f2.Rectangle.X)
                {
                    retorno = -1;
                }
                else if (f1.Rectangle.X > f2.Rectangle.X)
                {
                    retorno = 1;
                }
            }
            return retorno;
        }

        public bool SortFacelets()
        {
            if (this.facelets.Count == 9)
            {
                facelets.Sort(new Comparison<CubeFacelet>(SortFaceletsDelegate));
                for (int i = 0; i < facelets.Count; i++)
                {
                    facelets[i].Square = (CubeFaceletType)i;
                }
                return true;
            }
            return false;
        }

    }
}
