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
using static DLL_Borisov.Class1;

namespace Практика_Борисов.Properties
{
    public partial class Solving2 : Form
    {
        public Solving2()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            double X1, X2, Y1, Y2;
            double value_return, value_ref = -1, value_out;

            try
            {
                X1 = Input(textBoxX1);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBoxX1, "Вводите только числа в поля для ввода данных");
                return;
            }

            try
            {
                X2 = Input(textBoxX2);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBoxX2, "Вводите только числа в поля для ввода данных");
                return;
            }

            try
            {
                Y1 = Input(textBoxY1);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBoxY1, "Вводите только числа в поля для ввода данных");
                return;
            }

            try
            {
                Y2 = Input(textBoxY2);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBoxY2, "Вводите только числа в поля для ввода данных");
                return;
            }

            try
            {
                value_return = function_task2(X1, Y1, X2, Y2);
                function_task2_out(X1, Y1, X2, Y2, out value_out);
                function_task2_ref(X1, Y1, X2, Y2, ref value_ref);
            }
            catch (Exception Ex)
            {
                errorProvider1.SetError(textBox_return, "При вычислениях произошла ошибка. Введите другие данные");
                errorProvider1.SetError(textBox_ref, "При вычислениях произошла ошибка. Введите другие данные");
                errorProvider1.SetError(textBox_return, "При вычислениях произошла ошибка. Введите другие данные");
                return;
            }

            if (Double.IsNaN(value_return))
            {
                errorProvider1.SetError(textBox_ref, "Ответ не является действительным числом");
            }
            else
            {
                Output(textBox_ref, value_return);
            }

            if (Double.IsNaN(value_out))
            {
                errorProvider1.SetError(textBox_return, "Ответ не является действительным числом");
            }
            else
            {
                Output(textBox_return, value_out);
            }

            if (Double.IsNaN(value_ref))
            {
                errorProvider1.SetError(textBox_out, "Ответ не является действительным числом");
            }
            else
            {
                Output(textBox_out, value_ref);
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
            Task2 f = new Task2();
            this.Hide();
            f.ShowDialog();
        }
    }
}
