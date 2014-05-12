using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using RubikCube;

namespace RubikCubeSolver
{
    public static class CubeDiagramFiller
    {
        private static readonly Point[,] positions = new Point[,]
        {
            {
                new Point(127,7),new Point(146,7),new Point(165,7),
                new Point(127,26),new Point(146,26),new Point(165,26),
                new Point(127,46),new Point(146,46),new Point(165,46)
            },
            {
                new Point(127,133),new Point(146,133),new Point(165,133),
                new Point(127,152),new Point(146,152),new Point(165,152),
                new Point(127,172),new Point(146,172),new Point(165,172)
            },
            {
                new Point(64,70),new Point(83,70),new Point(102,70),
                new Point(64,89),new Point(83,89),new Point(102,89),
                new Point(64,108),new Point(83,108),new Point(102,108)
            },
            {
                new Point(190,70),new Point(209,70),new Point(228,70),
                new Point(190,89),new Point(209,89),new Point(228,89),
                new Point(190,108),new Point(209,108),new Point(228,108)
            },
            {
                new Point(127,70),new Point(146,70),new Point(165,70),
                new Point(127,89),new Point(146,89),new Point(165,89),
                new Point(127,108),new Point(146,108),new Point(165,108)
            },
            {
                new Point(127,196),new Point(146,196),new Point(165,196),
                new Point(127,215),new Point(146,215),new Point(165,215),
                new Point(127,234),new Point(146,234),new Point(165,234)
            }
        };

        public static Point GetPoint(CubeFaceType face, CubeFaceletType square)
        {
            return positions[face.GetHashCode(), square.GetHashCode()];
        }
    }
}
