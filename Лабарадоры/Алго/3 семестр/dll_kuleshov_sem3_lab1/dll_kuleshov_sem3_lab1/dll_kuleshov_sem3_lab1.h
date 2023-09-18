// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа DLLKULESHOVSEM3LAB1_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции DLLKULESHOVSEM3LAB1_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef DLLKULESHOVSEM3LAB1_EXPORTS
#define DLLKULESHOVSEM3LAB1_API __declspec(dllexport)
#else
#define DLLKULESHOVSEM3LAB1_API __declspec(dllimport)
#endif

// Этот класс экспортирован из библиотеки DLL
class DLLKULESHOVSEM3LAB1_API Cdllkuleshovsem3lab1 {
public:
	Cdllkuleshovsem3lab1(void);
	// TODO: добавьте сюда свои методы.
};

extern DLLKULESHOVSEM3LAB1_API int ndllkuleshovsem3lab1;

DLLKULESHOVSEM3LAB1_API int fndllkuleshovsem3lab1(void);


#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace dll_kuleshov_sem3_lab1 {
	public ref class Functions_Class
	{
	public:
		// ЛР #1
		
		static double input(TextBox^ t);
		static void output(double x, TextBox^ t);
		
		static double get_Radius(double L);
		public static double get_Length(double R);
		// ЛР #2
		static void input_mas(int* mas, int n);
		static void output_mas(int* mas, int len, DataGridView^ grid);

		static double count_in_bounds(int* mas, int n);
		static void set_mas(int* mas, int* rezmas, int n, double k, int& j);

		// TODO: Добавьте сюда свои методы для этого класса.
	};
}
