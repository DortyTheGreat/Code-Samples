using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLL_Borisov
{
    public class Class1
    {
        // Функция для ввода данных с TextBox
        public static double Input(TextBox t)
        {
            return Convert.ToDouble(t.Text);
        }

        // Функция для вывода данных на TextBox 
        public static void Output(TextBox t, double c)
        {
            t.Text = c.ToString("0.0000");
        }

        // Решение первой задачи через return
        public static double function_task1(double x)
        {
            return ((1d / 7d) + Math.Log(Math.Sqrt(x)) ) * Math.Exp(Math.Sqrt(Math.Abs(x-2)));
        }

        // Решение первой задачи через out
        public static void function_task1_out(double x, out double res)
        {
            res = ((1d / 7d) + Math.Log(Math.Sqrt(x))) * Math.Exp(Math.Sqrt(Math.Abs(x - 2)));
        }

        // Решение первой задачи через ref
        public static void function_task1_ref(double x, ref double res)
        {
            res = ((1d / 7d) + Math.Log(Math.Sqrt(x))) * Math.Exp(Math.Sqrt(Math.Abs(x - 2)));
        }

        // Решение второй задачи через return
        public static double function_task2(double x1, double y1, double x2, double y2)
        {
            double cos_a = (x1 * x2 + y1 * y2) / (Math.Sqrt(x1 * x1 + y1 * y1) * Math.Sqrt(x2 * x2 + y2 * y2));
            return Math.Acos(cos_a);
        }

        // Решение второй задачи через ref
        public static void function_task2_ref(double x1, double y1, double x2, double y2, ref double res)
        {
            double cos_a = (x1 * x2 + y1 * y2) / (Math.Sqrt(x1 * x1 + y1 * y1) * Math.Sqrt(x2 * x2 + y2 * y2));
            res = Math.Acos(cos_a);
        }

        // Решение второй задачи через out
        public static void function_task2_out(double x1, double y1, double x2, double y2, out double res)
        {
            double cos_a = (x1 * x2 + y1 * y2) / (Math.Sqrt(x1 * x1 + y1 * y1) * Math.Sqrt(x2 * x2 + y2 * y2));
            res = Math.Acos(cos_a);
        }
    }
}
