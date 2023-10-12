#include "pch.h"

#include "dll_kuleshov_projprac_sem3.h"

using namespace System::Windows::Forms;
using namespace System;


namespace dllkuleshovprojpracsem3 {
	int Functions::GetCheckBoxScore(CheckBox^ CB1, CheckBox^ CB2, CheckBox^ CB3, bool S1, bool S2, bool S3) {
		int ans = 0;
		ans += CB1->Checked == S1;
		ans += CB2->Checked == S2;
		ans += CB3->Checked == S3;
		return ans;

	}
}