using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace RubikCube
{
    public enum CubeFaceType
    {
        U = 0,
        D = 1,
        L = 2,
        R = 3,
        F = 4,
        B = 5
    }

    public enum CubeFaceColor
    {
        B = 0,
        Y = 1,
        O = 2,
        W = 3,
        G = 4,
        R = 5
    }

    public enum CubeFaceletType
    {
        UpLeft = 0,
        UpMid = 1,
        UpRight = 2,
        MidLeft = 3,
        Center = 4,
        MidRight = 5,
        DownLeft = 6,
        DownMid = 7,
        DownRight = 8
    }

    public enum CoordinateAxis
    {
        X = 0,
        Y = 1,
        Z = 2
    }

    public enum TurnType
    {
        HalfTurnRight = 0,
        HalfTurnLeft = 1,
        FullTurn = 2
    }
}
