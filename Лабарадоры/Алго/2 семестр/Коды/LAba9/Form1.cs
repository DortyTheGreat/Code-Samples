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

        int[] permute(int n, int[] arr)
        {
            int pos = 0;
            int neg = 0;

            for (int i = 0; i < n; ++i)
            {
                if (arr[i] > 0)
                {
                    pos++; continue;
                }

                if (arr[i] < 0)
                {
                    neg++;
                }
            }

            if (neg != pos) return arr;

            int[] new_arr = new int[n];

            for(int i = 0; i < n/2; ++i)
            {
                new_arr[i] = arr[i * 2];
                new_arr[n / 2 + i] = arr[i * 2 + 1];
            }
            return new_arr;
        }

        private void button1_Click(object sender, EventArgs e)
        {

            listBox1.Items.Clear();
            listBox2.Items.Clear();

            int n = int.Parse(textBox1.Text);
            int a = int.Parse(textBox2.Text);
            int b = int.Parse(textBox3.Text);
            int[] arr = new int[n];
            Random rnd = new Random();
            for (int i = 0;i < n; ++i)
            {
                arr[i] = rnd.Next() % (b-a+1) + a;
                listBox1.Items.Insert(i, arr[i]);
                Console.WriteLine(arr[i]);
            }
            arr = permute(n, arr);

            for (int i = 0; i < n; ++i)
            {
                listBox2.Items.Insert(i, arr[i]);
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
