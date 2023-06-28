using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace dll_for_prac
{
    public class Class1
    {
        // Ввод данных с обработкой ошибки (входные данные могут быть не преобразованны при конвертации). Возвращает корректность процесса конвертации
        public static bool Input(TextBox t, out double value, ErrorProvider EP, String error)
        {
            try
            {
                value = Convert.ToDouble(t.Text);
                return true;
            }
            catch (Exception Ex)
            {
                EP.SetError(t, error);
                value = 0;
                return false;
            }
        }

        // Вывод данных с обработкой ошибки (double переменная может иметь тип NaN)
        public static void Output(TextBox t, double c, ErrorProvider EP, String error)
        {
            if (Double.IsNaN(c))
            {
                EP.SetError(t, error);
            }
            else
            {
                t.Text = c.ToString("0.00000");
            }
        }

        // Функция для решения первого задания (через return)
        public static double func_for_zad1(double x)
        {
            return Math.Abs(x * Math.Log(x) - 4d / 7d) * Math.Sqrt(x) / Math.Exp((4 * x - 1.1d) / 5);
        }

        // Функция для решения первого задания (через out)
        public static void func_for_zad1_out(double x, out double res)
        {
            res = Math.Abs(x * Math.Log(x) - 4d / 7d) * Math.Sqrt(x) / Math.Exp((4 * x - 1.1d) / 5);
        }

        // Функция для решения первого задания (через ref)
        public static void func_for_zad1_ref(double x, ref double res)
        {
            res = Math.Abs(x * Math.Log(x) - 4d / 7d) * Math.Sqrt(x) / Math.Exp((4 * x - 1.1d) / 5);
        }

        // Функция для решения второго задания (через return)
        public static double func_for_zad2(double L)
        {
            // L = 2 PI R => R = L/(2 * PI)
            double R = L / (2 * Math.PI);
            double S = Math.PI * R * R;
            return S;
        }

        // Функция для решения второго задания (через out)
        public static void func_for_zad2_out(double L, out double res)
        {
            // L = 2 PI R => R = L/(2 * PI)
            double R = L / (2 * Math.PI);
            double S = Math.PI * R * R;
            res = S;
        }

        // Функция для решения второго задания (через ref)
        public static void func_for_zad2_ref(double L, ref double res)
        {
            // L = 2 PI R => R = L/(2 * PI)
            double R = L / (2 * Math.PI);
            double S = Math.PI * R * R;
            res = S;
        }

        public static double func_for_zad3(double x, double y, double a)
        {
            if (x < 0)
            {
                double m = 0;
                if (a < Math.Pow(x, a)) m = a; else m = Math.Pow(x, a);
                if (Math.Exp(x * a) < m) m = Math.Exp(x * a);
                if (a * x + 1 > m) m = a * x + 1;
                return m;
            }
            else
            {
                if (x >= 0 && x < 7)
                {
                    double m = 0;
                    if (x > y) m = x; else m = y;
                    return Math.Pow(Math.Cos(x), 2) + Math.Sin(Math.Pow(x, 2)) * m;
                }
                else
                {
                    return 1 + 3 * Math.Cos(Math.Abs(x + y));
                }
            }
        }

    }
}