using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace Проект_ЛР1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            

            InitializeComponent();
            
        }



        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        double sqr(double arg)
        {
            return arg * arg;
        }

        // Теорема Пифагора. C = sqrt(a^2 + b^2)
        double Pythagoras(double x1, double x2, double y1, double y2)
        {
            return Math.Sqrt(sqr(x1 - x2) + sqr(y1 - y2));
        }

        // Теорема Герона. Вычисляет площадь треугольника по заданным сторонам
        double Heron(double A, double B, double C)
        {
            double Pp = (A + B + C) / 2;
            return Math.Sqrt(Pp * (Pp - A) * (Pp - B) * (Pp - C));
        }

        private void ButtonCalc_Click(object sender, EventArgs e)
        {
            double x1 = Double.Parse(textBoxX1.Text);
            double x2 = Double.Parse(textBoxX2.Text);
            double x3 = Double.Parse(textBoxX3.Text);
            double y1 = Double.Parse(textBoxY1.Text);
            double y2 = Double.Parse(textBoxY2.Text);
            double y3 = Double.Parse(textBoxY3.Text);

            double A = Pythagoras(x1, x2, y1, y2);
            double B = Pythagoras(x2, x3, y2, y3);
            double C = Pythagoras(x3, x1, y3, y1); ;

            double P = A + B + C;

            if (A <= 0 || B <= 0 || C <= 0 || A + B < +C || A + C <= B || B + C <= A) return;

            double S = Heron(A, B, C);

            textBoxP.Text = P.ToString();
            textBoxS.Text = S.ToString();

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label7.Text = "Задание: Создать проект, вычисляющий периметр и площадь\nтреугольница по заданным координатам трех вершин";
        }

        private void label8_Click(object sender, EventArgs e)
        {

        }
    }
}
