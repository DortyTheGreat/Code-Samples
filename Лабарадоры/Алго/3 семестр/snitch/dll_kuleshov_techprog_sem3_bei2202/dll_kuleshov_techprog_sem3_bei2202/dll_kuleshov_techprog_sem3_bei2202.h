#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace dll_kuleshov_techprog_sem3_bei2202 {
	public ref class Functions_Class
	{
		public:
			// ЛР #1

			static double input(TextBox^ t);
			static void output(double x, TextBox^ t);

			static double get_Radius(double L);
			static double get_Length(double L);

			// ЛР #2
			static void gen_mas(int* mas, int n);
			static void output_mas(int* mas, int len, DataGridView^ grid);

			static int count_in_bounds(int* mas, int n);
			static void set_mas(int* mas, int n, int* rezmas);

	};
}
