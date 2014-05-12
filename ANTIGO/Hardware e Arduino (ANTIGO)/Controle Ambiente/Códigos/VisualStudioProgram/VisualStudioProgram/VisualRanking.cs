using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VisualStudioProgram
{
    public partial class VisualRanking : Component
    {
        public VisualRanking()
        {
            InitializeComponent();
        }

        public VisualRanking(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
        }
    }
}
