#include "Titul.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	//KuleshovProjPracsem3::Questions^ f = gcnew KuleshovProjPracsem3::Questions();

	KuleshovProjPracsem3::Titul form;

	Application::Run(% form);

}