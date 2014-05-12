using System;
using System.Collections.Generic;
using System.Text;
using RubikCube;
using System.Threading;
using ImageAnalysis;
using ArduinoCommunication;

namespace CubeSolver
{
    public static class CubeAnalyser
    {
        public static System.Drawing.Image SourceImage;

        public static Cube AnalyseCube(List<ColorFilter> filters, int faceletMinWidth, int faceletMinHeight, ArduinoChannel channel)
        {
            /*
              1- Get all images from Arduino
              2- Open a thread to each face and call ImageAnalyser.AnalyseImageSample()
              3- Wait all 6 threads
              4- Sort the positions of the facelets to the 6 faces
              5- Create the string of original cube      
              6- Create new cube
           */
            if (channel == null)
            {
                return null;
            }

            // inicializa visão do Arduino
            channel.SendInitVision();

            Cube newCube = new Cube();

            const int nFaces = 6;
            ManualResetEvent[] doneEvents = new ManualResetEvent[nFaces];
            ImageSample imgSmp = new ImageSample();
            imgSmp.FaceletMinWidth = faceletMinWidth;
            imgSmp.FaceletMinHeight = faceletMinHeight;
            List<ImageAnalyser> analysers = new List<ImageAnalyser>();
            for (int i = 0; i < nFaces; i++)
            {
                doneEvents[i] = new ManualResetEvent(false);
                ImageAnalyser imgAn = new ImageAnalyser();
                imgAn.Filters = filters;
                imgSmp.FaceNumber = i;

                PositioningFace(channel, i+1);
                imgSmp.SampleImg = CubeAnalyser.SourceImage;

                imgAn.Sample = imgSmp.Clone();
                analysers.Add(imgAn);
                ThreadPool.QueueUserWorkItem(imgAn.AnalyseImageSample, doneEvents[i]);
            }
            foreach (ManualResetEvent item in doneEvents)
            {
                WaitHandle hdl = (WaitHandle)item;
                hdl.WaitOne();
            }

            int[] faces;
            Dictionary<CubeFace, CubeFaceType> cubeMap = new Dictionary<CubeFace, CubeFaceType>();
            for (int i = 0; i < nFaces; i++)
            {
                Dictionary<CubeFaceletType, CubeFaceColor> tmpFacelets = new Dictionary<CubeFaceletType, CubeFaceColor>();
                faces = SortFacelets((CubeFaceType)i);
                for (int j = 0; j < 9; j++)
                {
                    tmpFacelets.Add((CubeFaceletType)faces[j], GetCubeFaceColor(analysers[i].Sample.Cores[j]));
                }
                cubeMap.Add(new CubeFace(tmpFacelets), (CubeFaceType)i);
            }
            newCube = new Cube(cubeMap);
            return newCube;
        }

        private static bool PositioningFace(ArduinoChannel channel, int numberFace)
        {
            RotateCubeMovement rotMov = new RotateCubeMovement();

            switch (numberFace)
            {
                case 1:
                    // não faz nada, é a primeira face
                    break;
                case 2:
                    rotMov.Axis = CoordinateAxis.Y;
                    rotMov.Type = TurnType.HalfTurnRight;
                    channel.SendVisualizationMovement(rotMov);
                    break;
                case 3:
                    rotMov.Axis = CoordinateAxis.Y;
                    rotMov.Type = TurnType.HalfTurnRight;
                    channel.SendVisualizationMovement(rotMov);
                    break;
                case 4:
                    rotMov.Axis = CoordinateAxis.Y;
                    rotMov.Type = TurnType.HalfTurnRight;
                    channel.SendVisualizationMovement(rotMov);
                    break;
                case 5:
                    rotMov.Axis = CoordinateAxis.X;
                    rotMov.Type = TurnType.HalfTurnRight;
                    channel.SendVisualizationMovement(rotMov);

                    rotMov = new RotateCubeMovement();
                    rotMov.Axis = CoordinateAxis.Y;
                    rotMov.Type = TurnType.HalfTurnRight;
                    channel.SendVisualizationMovement(rotMov);
                    break;
                case 6:
                    rotMov.Axis = CoordinateAxis.Y;
                    rotMov.Type = TurnType.FullTurn;
                    channel.SendVisualizationMovement(rotMov);
                    break;
                default:
                    return false;
            }
            return true;
        }

        private static CubeFaceColor GetCubeFaceColor(System.Drawing.Color c)
        {
            if (IsColorEqual(c, System.Drawing.Color.White))
                return CubeFaceColor.W;
            if (IsColorEqual(c, System.Drawing.Color.Red))
                return CubeFaceColor.R;
            if (IsColorEqual(c, System.Drawing.Color.Green))
                return CubeFaceColor.G;
            if (IsColorEqual(c, System.Drawing.Color.Blue))
                return CubeFaceColor.B;
            if (IsColorEqual(c, System.Drawing.Color.Yellow))
                return CubeFaceColor.Y;
            if (IsColorEqual(c, System.Drawing.Color.FromArgb(255, 128, 0)))
                return CubeFaceColor.O;
            return CubeFaceColor.W;
        }

        private static bool IsColorEqual(System.Drawing.Color c1, System.Drawing.Color c2)
        {
            return c1.R == c2.R && c1.G == c2.G && c1.B == c2.B;
        }

        private static int[] SortFacelets(CubeFaceType face)
        {
            int[] faceUL = { 
                               (int)CubeFaceletType.UpLeft, (int)CubeFaceletType.UpMid,(int)CubeFaceletType.UpRight,
                               (int)CubeFaceletType.MidLeft,(int)CubeFaceletType.Center, (int)CubeFaceletType.MidRight,
                               (int)CubeFaceletType.DownLeft, (int)CubeFaceletType.DownMid,(int)CubeFaceletType.DownRight 
                           };
            int[] faceUR = { 
                               (int)CubeFaceletType.UpRight, (int)CubeFaceletType.MidRight,(int)CubeFaceletType.DownRight,
                               (int)CubeFaceletType.UpMid,(int)CubeFaceletType.Center, (int)CubeFaceletType.DownMid,
                               (int)CubeFaceletType.UpLeft, (int)CubeFaceletType.MidLeft,(int)CubeFaceletType.DownLeft 
                           };
            int[] faceDL = { 
                               (int)CubeFaceletType.DownLeft, (int)CubeFaceletType.MidLeft,(int)CubeFaceletType.UpLeft,
                               (int)CubeFaceletType.DownMid,(int)CubeFaceletType.Center, (int)CubeFaceletType.UpMid,
                               (int)CubeFaceletType.DownRight, (int)CubeFaceletType.MidRight,(int)CubeFaceletType.UpRight 
                           };
            int[] faceDR = {
                               (int)CubeFaceletType.DownRight,(int)CubeFaceletType.DownMid,(int)CubeFaceletType.DownLeft,
                               (int)CubeFaceletType.MidRight,(int)CubeFaceletType.Center,(int)CubeFaceletType.MidLeft,
                               (int)CubeFaceletType.UpRight,(int)CubeFaceletType.UpMid,(int)CubeFaceletType.UpLeft           
                           };
            switch (face)
            {
                case CubeFaceType.U:
                    return faceUR;
                case CubeFaceType.B:
                    return faceDL;
                case CubeFaceType.D:
                    return faceUR;
                case CubeFaceType.F:
                    return faceUR;
                case CubeFaceType.R:
                    return faceDR;
                case CubeFaceType.L:
                    return faceDR;
                default:
                    return faceUR;
            }
        }
    }
}
