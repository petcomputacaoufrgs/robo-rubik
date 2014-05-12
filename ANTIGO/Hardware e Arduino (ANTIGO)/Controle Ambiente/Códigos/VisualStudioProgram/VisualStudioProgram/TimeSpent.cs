using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VisualStudioProgram
{
    class TimeSpent : IComparable<TimeSpent>
    {
        private int MinDone { get; set; }
        private int SecDone { get; set; }
        private int CentSecDone { get; set; }

        public int CompareTo(TimeSpent other)
        {
            if (other == null) return 1;

            return this.calculateTimeInCentSec().CompareTo(other.calculateTimeInCentSec());
        }

        private int calculateTimeInCentSec()
        {
            return (MinDone * 6000) + (SecDone * 100) + CentSecDone;
        }
    }
}
