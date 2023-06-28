using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static dll_for_prac.Class1;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace prac_MTUCI
{
    public partial class task1 : Form
    {
        public task1()
        {
            InitializeComponent();
        }

        private void Calculate_Click(object sender, EventArgs e)
        {
            double x1, x2, x3;
            double ans1, ans2, ans3 = 0;
            String final_content = "Задание №1\n\n";
            if (Input(textBox1, out x1, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой"))
            {
                try
                {
                    ans1 = func_for_zad1(x1);
                    final_content += "Входные данные(return): " + x1 + '\n';
                    final_content += "Выходные данные(return): " + ans1 + "\n\n";
                    Output(textBox4, ans1, errorProvider1, "Результатом вычисления является не действительное число");
                }
                catch (Exception Ex)
                {
                    errorProvider1.SetError(textBox4, "Во время вычислений произошла ошибка");
                }
                
            }

            if (Input(textBox2, out x2, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой"))
            {
                try
                {
                    func_for_zad1_out(x2, out ans2);
                    final_content += "Входные данные(out): " + x2 + '\n';
                    final_content += "Выходные данные(out): " + ans2 + "\n\n";
                    Output(textBox5, ans2, errorProvider1, "Результатом вычисления является не действительное число");
                }
                catch (Exception Ex)
                {
                    errorProvider1.SetError(textBox5, "Во время вычислений произошла ошибка");
                }

            }

            if (Input(textBox3, out x3, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой"))
            {
                try
                {
                    func_for_zad1_ref(x3, ref ans3);
                    final_content += "Входные данные(ref): " + x3 + '\n';
                    final_content += "Выходные данные(ref): " + ans3 + "\n\n";
                    Output(textBox6, ans3, errorProvider1, "Результатом вычисления является не действительное число");
                }
                catch (Exception Ex)
                {
                    errorProvider1.SetError(textBox6, "Во время вычислений произошла ошибка");
                }

            }

            System.IO.File.WriteAllText("task1.txt", final_content);
        }

        private void task1_Load(object sender, EventArgs e)
        {

        }

        private void to_statement_Click(object sender, EventArgs e)
        {
            task2_statement f = new task2_statement();
            this.Hide();
            f.ShowDialog();
        }
    }
}
