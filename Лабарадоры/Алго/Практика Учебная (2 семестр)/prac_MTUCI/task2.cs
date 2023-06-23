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
using static dll_for_prac.Class1;

namespace prac_MTUCI
{
    public partial class task2 : Form
    {
        public task2()
        {
            InitializeComponent();
        }

        private void to_statement_Click(object sender, EventArgs e)
        {
            task2_statement f = new task2_statement();
            this.Hide();
            f.ShowDialog();
        }

        private void Calculate_Click(object sender, EventArgs e)
        {
            double L1, L2, L3;
            double S1, S2 = 0, S3;

            if (Input(textBoxL1, out L1, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой"))
            {
                try
                {
                    S1 = func_for_zad2(L1);
                    Output(textBoxS1, S1, errorProvider1, "Результатом вычисления является не действительное число");
                }
                catch (Exception Ex)
                {
                    errorProvider1.SetError(textBoxS1, "Во время вычислений произошла ошибка");
                }
            }

            if (Input(textBoxL2, out L2, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой"))
            {
                try
                {
                    func_for_zad2_ref(L2, ref S2);
                    Output(textBoxS2, S2, errorProvider1, "Результатом вычисления является не действительное число");
                }
                catch (Exception Ex)
                {
                    errorProvider1.SetError(textBoxS2, "Во время вычислений произошла ошибка");
                }
            }

            if (Input(textBoxL3, out L3, errorProvider1, "В поля для ввода данных допускается лишь ввод числовых значений с плавающей точкой"))
            {
                try
                {
                    func_for_zad2_out(L3, out S3);
                    Output(textBoxS3, S3, errorProvider1, "Результатом вычисления является не действительное число");
                }
                catch (Exception Ex)
                {
                    errorProvider1.SetError(textBoxS3, "Во время вычислений произошла ошибка");
                }
            }
        }
    }
}
