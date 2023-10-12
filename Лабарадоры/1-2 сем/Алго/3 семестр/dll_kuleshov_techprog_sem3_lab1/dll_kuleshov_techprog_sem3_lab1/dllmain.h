#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace DLLTechProgVasilyevBEI2202 {
	public ref class Functions_Class
	{
		public:
			// ЛР №1
			static double pyramid_square(double ab, double ad, double db,
										 double dc, double bc, double ac);
			static double input_tbox(TextBox^ t);
			static void output_tbox(double x, TextBox^ t);

			// ЛР №2
			static void input_mas(int* mas, int n);
			static void output_mas(int* mas, int len, DataGridView^ grid);
			static double geom_mean(int* mas, int n);
			static void set_mas(int* mas, int* rezmas, int n, double k, int& j);

		// TODO: Добавьте сюда свои методы для этого класса.
	};
}
