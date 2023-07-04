using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static DLL_Borisov.Class1;

namespace Практика_Борисов.Properties
{
    public partial class Solving1 : Form
    {
        public Solving1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            double x;
            double value_return, value_ref = -1, value_out;

            try
            {
                x = Input(textBox1);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBox1, "Вводите только числа в поля для ввода данных");
                return;
            }

            try
            {
                value_return = function_task1(x);
                function_task1_out(x, out value_out);
                function_task1_ref(x, ref value_ref);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBox2, "При вычислениях произошла ошибка. Введите другие данные");
                errorProvider1.SetError(textBox3, "При вычислениях произошла ошибка. Введите другие данные");
                errorProvider1.SetError(textBox4, "При вычислениях произошла ошибка. Введите другие данные");
                return;
            }

            if (Double.IsNaN(value_return))
            {
                errorProvider1.SetError(textBox2, "Ответ не является действительным числом");
            }
            else
            {
                Output(textBox2, value_return);
            }

            if (Double.IsNaN(value_ref))
            {
                errorProvider1.SetError(textBox3, "Ответ не является действительным числом");
            }
            else
            {
                Output(textBox3, value_ref);
            }

            if (Double.IsNaN(value_out))
            {
                errorProvider1.SetError(textBox4, "Ответ не является действительным числом");
            }
            else
            {
                Output(textBox4, value_out);
            }


        }

        private void button3_Click(object sender, EventArgs e)
        {
            MainForm f = new MainForm();
            this.Hide();
            f.ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Task1 f = new Task1();
            this.Hide();
            f.ShowDialog();

        }
    }
}
