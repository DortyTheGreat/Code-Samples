#include "Main.h"
#include "lab1_condition.h"
#include "lab1_solution.h"
#include "lab2_condition.h"
#include "lab2_solution.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	kuleshov_techprog_sem3_bei2202::Main form;
	Application::Run(% form);
}