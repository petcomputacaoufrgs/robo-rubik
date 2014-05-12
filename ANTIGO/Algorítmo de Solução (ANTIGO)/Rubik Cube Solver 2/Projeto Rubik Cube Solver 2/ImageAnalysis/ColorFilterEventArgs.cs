using System;
using System.Collections.Generic;
using System.Text;

namespace ImageAnalysis
{
    /// <summary>
    /// EventArgs to ColorFilterDialog events
    /// </summary>
    public class ColorFilterEventArgs : EventArgs
    {
        /// <summary>
        /// The type of the occured settings change
        /// </summary>
        public TypeFilterChanged ChangeType { get; set; }
    }
}
