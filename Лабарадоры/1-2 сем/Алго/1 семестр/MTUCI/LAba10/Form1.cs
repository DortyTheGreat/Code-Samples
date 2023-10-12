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


            listBox2.Items.Clear();

            string data = textBox1.Text;

            int size = data.Count(t => t == '\n') + 1;

            Console.WriteLine(data);
            
            int[] arr = new int[size];
            int h = 0;
            string carret = "";
            for(int i = 0;i < data.Length; ++i)
            {
                if (data[i] == '\n'){
                    arr[h++] = Int32.Parse(carret);
                    carret = "";
                }else{
                    carret += data[i];
                }
                
            }

            arr[h++] = Int32.Parse(carret);

            
            arr = permute(size, arr);

            for (int i = 0; i < size; ++i)
            {
                listBox2.Items.Insert(i, arr[i]);
            }
            

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
