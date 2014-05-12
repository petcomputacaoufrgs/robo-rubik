using System;
using System.Collections.Generic;
using System.Text;
using RubikCube;
using System.Threading;
using ImageAnalysis;

namespace CubeSolver
{
    public static class CubeAnalyser
    {
        public static Cube AnalyseCube(List<ColorFilter> filters, int faceletMinWidth, int faceletMinHeight)
        {
  /*
    1- Get all images from Arduino
    2- Open a thread to each face and call ImageAnalyser.AnalyseImageSample()
    3- Wait all 6 threads
    4- Sort the positions of the facelets to the 6 faces
    5- Create the string of original cube      
    6- Create new cube
 */
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
                /*
                 * Aqui, deve ser colocado o trecho de código
                 * em que é pedi ao arduino que faça os movimentos
                 * para posicionar a face desejada para a câmera.
                 * Ao final, não esquecer de setar a propriedade Sample, do objeto imgSmp
                    Ex.: imgSmp.Sample = image;
                 */
                imgAn.Sample = imgSmp.Clone();
                analysers.Add(imgAn);
                ThreadPool.QueueUserWorkItem(imgAn.AnalyseImageSample, i);
            }
            WaitHandle.WaitAll(doneEvents);

            return newCube;
        }
    }
}
