using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace RubikCube
{

    public static class ColorTranslate
    {
        public static Color getColorByEnumValue(CubeFaceColor color)
        {
            switch (color)
            {
                case CubeFaceColor.B:
                    return Color.Blue;
                case CubeFaceColor.G:
                    return Color.Green;
                case CubeFaceColor.O:
                    return Color.Orange;
                case CubeFaceColor.R:
                    return Color.Red;
                case CubeFaceColor.W:
                    return Color.White;
                case CubeFaceColor.Y:
                    return Color.Yellow;
            }
            return Color.Blue;
        }

        public static CubeFaceColor getFaceColorByColor(Color color)
        {
            if (color.Equals(Color.Blue))
            {
                return CubeFaceColor.B;
            }
            else if (color.Equals(Color.Red))
            {
                return CubeFaceColor.R;
            }
            else if (color.Equals(Color.White))
            {
                return CubeFaceColor.W;
            }
            else if (color.Equals(Color.Orange))
            {
                return CubeFaceColor.O;
            }
            else if (color.Equals(Color.Yellow))
            {
                return CubeFaceColor.Y;
            }
            else if (color.Equals(Color.Green))
            {
                return CubeFaceColor.G;
            }
            return CubeFaceColor.B;
        }
    }
}
