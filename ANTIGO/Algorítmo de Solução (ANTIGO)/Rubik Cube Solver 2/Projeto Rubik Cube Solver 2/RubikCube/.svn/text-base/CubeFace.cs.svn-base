using System;
using System.Collections.Generic;
using System.Text;

namespace RubikCube
{
    public class CubeFace
    {
        private Dictionary<CubeFaceletType, CubeFaceColor> Facelets { get; set; }
        public CubeFaceColor Center { get; set; }

        public CubeFace(Dictionary<CubeFaceletType, CubeFaceColor> facelets)
        {
            Facelets = facelets;
            CubeFaceColor color;
            if (facelets.TryGetValue(CubeFaceletType.Center, out color))
            {
                Center = color;
            }
        }

        public CubeFace(CubeFaceColor center)
        {
            Center = center;
        }

        public void AddFacelets(Dictionary<CubeFaceletType, CubeFaceColor> facelets)
        {
            Facelets = facelets;
            CubeFaceColor color;
            if (facelets.TryGetValue(CubeFaceletType.Center, out color))
            {
                Center = color;
            }
        }

        public bool Validate()
        {
            if ((Facelets.Count == 9) && (Center != null))
            {
                return true;
            }
            return false;
        }

        public Dictionary<CubeFaceletType, CubeFaceColor> getFacelets()
        {
            return Facelets;
        }
    }
}
