using System;
using System.Collections.Generic;
using System.Text;

namespace VideoCapture
{
    /// <summary>
    /// EventArgs to the ImageCaptured event
    /// </summary>
    public class ImageCapturedEventArgs : EventArgs
    {
        #region Fields

        private System.Drawing.Image m_Image;
        private ulong m_FrameNumber = 0;

        #endregion

        #region Props

        /// <summary>
        ///  WebCamImage
        ///  This is the image returned by the web camera capture
        /// </summary>
        public System.Drawing.Image WebCamImage
        {
            get
            { return m_Image; }

            set
            { m_Image = value; }
        }

        /// <summary>
        /// FrameNumber
        /// Holds the sequence number of the frame capture
        /// </summary>
        public ulong FrameNumber
        {
            get
            { return m_FrameNumber; }

            set
            { m_FrameNumber = value; }
        }

        #endregion
    }
}
