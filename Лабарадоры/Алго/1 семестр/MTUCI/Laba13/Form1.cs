using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace LAba9
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
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
            string[] lines = System.IO.File.ReadAllLines(textBox1.Text);
            string final_content = "";
            for(int i = 0; i < lines.Length; ++i)
            {
                final_content += permute(lines[i]) + '\n';
                
            }
            System.IO.File.WriteAllText(textBox2.Text, final_content);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox2.Items.Clear();
            string[] lines = System.IO.File.ReadAllLines(textBox2.Text);
            for (int i = 0; i < lines.Length; ++i)
            {
                listBox2.Items.Insert(i, lines[i]);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            string[] lines = System.IO.File.ReadAllLines(textBox1.Text);
            for (int i = 0; i < lines.Length; ++i)
            {
                listBox1.Items.Insert(i, lines[i]);
            }
        }
    }
}
