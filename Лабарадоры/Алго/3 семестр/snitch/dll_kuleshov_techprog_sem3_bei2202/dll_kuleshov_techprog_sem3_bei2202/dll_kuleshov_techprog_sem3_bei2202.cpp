#include "pch.h"
#include "dll_kuleshov_techprog_sem3_bei2202.h"
#include "Math.h"
#include <cstdlib>
#include <time.h>

using namespace System::Windows::Forms;
namespace dll_kuleshov_techprog_sem3_bei2202 {


	double Functions_Class::input(TextBox^ t) {
		return Convert::ToDouble(t->Text);
	}

	void Functions_Class::output(double x, TextBox^ t) {
		t->Text = Convert::ToString(x);
	}

	double Functions_Class::get_Radius(double L) {
		return L / (2 * Math::PI);
	}

	double Functions_Class::get_Area(double L) {
		double S = Math::PI * Math::Pow(get_Radius(L), 2);
		return S;
	}

	

// ЛР №2
	void Functions_Class::gen_mas(double* mas, int n) {
		srand(time(0));
		for (int i = 0; i < n; i++) {
			mas[i] = ((double)((int)(rand() % 600) - 300)) / 10.0;
		}
	}

	int Functions_Class::count_in_bounds(double* mas, int n) {
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (mas[i] >= 2 && mas[i] <= 10) {
				count++;
			}
		}
		return count;
	}

	

	void Functions_Class::output_mas(double* mas, int len, DataGridView^ grid) {
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

	int Functions_Class::set_mas(double* mas, int n, double* rezmas) {
		int cou = count_in_bounds(mas, n);
		int j = 0;
		for (int i = 0; i < n; i++) {
			if (mas[i] < cou) {
				rezmas[j] = mas[i];
				j++;
			}
		}
		return j;
	}
}