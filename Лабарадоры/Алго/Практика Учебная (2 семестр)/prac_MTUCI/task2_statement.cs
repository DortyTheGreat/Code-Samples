using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace prac_MTUCI
{
    public partial class task2_statement : Form
    {
        public task2_statement()
        {
            InitializeComponent();
        }

        private void to_main_Click(object sender, EventArgs e)
        {
            main f = new main();
            this.Hide();
            f.ShowDialog();
        }

        private void to_task_Click(object sender, EventArgs e)
        {
            task2 f = new task2();
            this.Hide();
            f.ShowDialog();
        }
    }
}
