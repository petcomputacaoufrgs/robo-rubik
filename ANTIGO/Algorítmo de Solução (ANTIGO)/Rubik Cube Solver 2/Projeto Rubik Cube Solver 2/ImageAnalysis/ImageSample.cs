using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace ImageAnalysis
{
    public class ImageSample
    {
        public Image Sample { get; set; }

        public int FaceNumber { get; set; }

        public int FaceletMinWidth { get; set; }

        public int FaceletMinHeight { get; set; } 

        public Dictionary<Rectangle, Color> Facelets = new Dictionary<Rectangle, Color>();

        public ImageSample Clone()
        {
            MemoryStream ms = new MemoryStream();
            BinaryFormatter bf = new BinaryFormatter();

            bf.Serialize(ms, this);

            ms.Position = 0;
            object obj = bf.Deserialize(ms);
            ms.Close();

            return obj as ImageSample;
        }
    }
}
