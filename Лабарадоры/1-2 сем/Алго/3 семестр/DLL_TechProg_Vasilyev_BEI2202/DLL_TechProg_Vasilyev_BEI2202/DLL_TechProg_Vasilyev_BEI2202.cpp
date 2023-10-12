#include "pch.h"
#include "DLL_TechProg_Vasilyev_BEI2202.h"
#include "Math.h"
#include <cstdlib>
#include <time.h>

using namespace System::Windows::Forms;
namespace DLLTechProgVasilyevBEI2202 {
// ЛР №1
	// Функция вычисления площади треугольника
	double square(double a, double b, double c) {
		a = abs(a);
		b = abs(b);
		c = abs(c);
		double p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	// Функция вычисления площади поверхности пирамиды
	double Functions_Class::pyramid_square(double ab, double ad, double db,
							double dc, double bc, double ac) {
		// Вычисление площадей граней
		double abd = square(ab, ad, db);
		double acd = square(ac, ad, dc);
		double bcd = square(bc, db, dc);
		double abc = square(ac, ab, bc);
		// Сумма площадей граней
		double answer = abd + acd + bcd + abc;
		return answer;
	}

	double Functions_Class::input_tbox(TextBox^ t) {
		return Convert::ToDouble(t->Text);
	}

	void Functions_Class::output_tbox(double x, TextBox^ t) {
		t->Text = Convert::ToString(x);
	}

// ЛР №2
	void Functions_Class::input_mas(int* mas, int n) {
		srand(time(0));
		for (int i = 0; i < n; i++) {
			mas[i] = (int)(rand() % 81) - 30;
		}
	}

	void Functions_Class::output_mas(int* mas, int len, DataGridView^ grid) {
		grid->ColumnCount = len;
		grid->RowCount = 2;
		for (int i = 0; i < len; i++) {
			grid->Rows[0]->Cells[i]->Value = "[" + i + "]";
			grid->Rows[1]->Cells[i]->Value = mas[i];
		}
		int width = 0;
		for (int s = 0; s < grid->ColumnCount; s++) {
			width += grid->Columns[s]->Width;
			if (width > 350)
				grid->Width = 350;
			else
				grid->Width = width+10;
		}
	}

	double Functions_Class::geom_mean(int* mas, int n) {
		int count = 0;
		unsigned long long int product = 2;
		for (int i = 0; i < n; i++) {
			if (mas[i] > 0) {
				unsigned int square = (mas[i] * mas[i]);
				product *= square;
				count++;
			}
		}
		double mean = pow(product, 1/count);
		return mean;
	}

	void Functions_Class::set_mas(int* mas, int* rezmas, int n, double k, int& j) {
		j = 0;
		for (int i = 0; i < n; i++) {
			if (mas[i] < k) {
				rezmas[j] = mas[i];
				j++;
			}
		}
	}
}