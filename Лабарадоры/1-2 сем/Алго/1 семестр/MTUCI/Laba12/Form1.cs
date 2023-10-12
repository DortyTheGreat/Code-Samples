using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace LAba9
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        String permute(String input)
        {
            String ret = "";
            if (input.Length > 0) ret = (input[0]).ToString();
            for(int i = 1;i < input.Length; ++i)
            {
                if (input[i - 1] != input[i]) ret += input[i];
            }
            return ret;
        }

        private void button1_Click(object sender, EventArgs e)
        {

            textBox2.Text = permute(textBox1.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

  
    }
}
