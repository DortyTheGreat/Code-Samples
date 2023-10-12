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

        double[,] permute(int n, double[,] arr, int nn)
        {
            double[,] new_arr = new double[nn, n];
            for (int row = 0; row < nn; ++row) {
                int pos = 0, neg = 0, h =0;

                for (int i = 0; i < n; ++i)
                {
                    if (arr[row, i] >= 0){
                        pos++; continue;
                    }

                    if (arr[row, i] < 0)
                        neg++;
                }

                if (neg != pos){ // Не менять массив
                    for (int i = 0; i < n; ++i){
                        new_arr[row, h++] = arr[row, i];
                    }
                    continue;
                }


                for (int i = 0; i < n; ++i){ // Положительные
                    if (arr[row, i] >= 0)
                        new_arr[row, h++] = arr[row, i];
                }

                for (int i = 0; i < n; ++i){ // Отрицательные
                    if (arr[row, i] < 0)
                        new_arr[row, h++] = arr[row, i];
                }

            }
            return new_arr;
        }

        private void button1_Click(object sender, EventArgs e)
        {

            listBox1.Items.Clear();
            listBox2.Items.Clear();

            int n = int.Parse(textBox1.Text);
            int m = int.Parse(textBox4.Text);
            int a = int.Parse(textBox2.Text);
            int b = int.Parse(textBox3.Text);

            double[,] arr = new double[n, m];

            Random rnd = new Random();
            for (int i = 0;i < n; ++i)
            {
                string str = "";
                for (int j = 0; j < m; ++j)
                {
                    arr[i,j] = rnd.NextDouble() * (b - a) + a;
                    str += arr[i, j].ToString("00.00") + " ";
                    Console.WriteLine(arr[i,j]);
                }
                listBox1.Items.Insert(i, str);
            }

            
            arr = permute(m, arr,n);


            for (int i = 0; i < n; ++i)
            {
                string str = "";
                for (int j = 0; j < m; ++j)
                {

                    str += arr[i, j].ToString("00.00") + " ";
                    Console.WriteLine(arr[i, j]);
                }
                listBox2.Items.Insert(i, str);
            }
            

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }
    }
}
