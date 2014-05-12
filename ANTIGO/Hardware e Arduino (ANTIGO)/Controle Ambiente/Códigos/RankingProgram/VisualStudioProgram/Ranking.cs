using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VisualStudioProgram
{
    public class Ranking
    {
        public static int MAX_POSITIONS = 10;

        private List<Competitor> bestCompetitors;

        #region Constructors
        public Ranking()
        {
            bestCompetitors = new List<Competitor>();
        }

        public Ranking(List<Competitor> bestList)
        {
            bestCompetitors = bestList;
        }
        #endregion

        public void AddPerson(Competitor c)
        {
            bestCompetitors.Add(c);
            bestCompetitors.Sort();
        }
    }
}
