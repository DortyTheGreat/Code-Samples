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
    public partial class task3 : Form
    {
        public task3()
        {
            InitializeComponent();
        }

        private void to_statement_Click(object sender, EventArgs e)
        {
            task3_statement f = new task3_statement();
            this.Hide();
            f.ShowDialog();
        }

        private void Calculate_Click(object sender, EventArgs e)
        {
            double value_return;
            double x, y, a;
            String final_content = "Задание №3\n\n";
            if (!Input(textBoxX, out x, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой")) return;

            if (!Input(textBoxY, out y, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой")) return;

            if (!Input(textBoxA, out a, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой")) return;

            value_return = func_for_zad3(x,y,a);

            Output(textBox_return, value_return, errorProvider1, "Результатом вычисления является не действительное число");

            final_content += "Входные данные(x, y, a): " + x + " " + y + " " + a + "\n\n";
            final_content += "Выходные данные: " + value_return + "\n";


            System.IO.File.WriteAllText("task3.txt", final_content);
        }

        private void textBoxY_KeyPress(object sender, KeyPressEventArgs e)
        {
            NumberLimiter(e, textBoxY);
        }

        private void textBoxX_KeyPress(object sender, KeyPressEventArgs e)
        {
            NumberLimiter(e, textBoxX);
        }

        private void textBoxA_KeyPress(object sender, KeyPressEventArgs e)
        {
            NumberLimiter(e, textBoxA);
        }
    }
}

