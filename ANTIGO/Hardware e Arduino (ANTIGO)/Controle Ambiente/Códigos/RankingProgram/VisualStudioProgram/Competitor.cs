using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VisualStudioProgram
{
    class Competitor : IComparable<Competitor>
    {
        private string Name { get; set; }
        private TimeSpent TimeUsed { get; set; }

        public Competitor(string name,TimeSpent timeUsed)
        {
            Name = name;
            TimeUsed = timeUsed;
        }

        public int CompareTo(Competitor other)
        {
            if (other == null) return 1;

            return this.TimeUsed.CompareTo(other.TimeUsed);
        }
    }
}
