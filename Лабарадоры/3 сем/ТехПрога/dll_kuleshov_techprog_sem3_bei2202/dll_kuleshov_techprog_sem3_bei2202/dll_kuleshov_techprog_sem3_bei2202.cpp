#include "pch.h"
#include "dll_kuleshov_techprog_sem3_bei2202.h"
#include "Math.h"
#include <cstdlib>
#include <time.h>

using namespace System::Windows::Forms;
using namespace System;
using namespace System::IO;
using namespace System::Data::OleDb;
using namespace System::Runtime::InteropServices;
using namespace Microsoft::Office::Interop;

using namespace System::Globalization;

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

	void Functions_Class::get_Area_mult(double L1, double& S1, double L2, double& S2, double L3, double& S3) {
		S1 = Functions_Class::get_Area(L1);
		S2 = Functions_Class::get_Area(L2);
		S3 = Functions_Class::get_Area(L3);
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
		grid->RowCount = 2;
		grid->ColumnCount = len;

		for (int i = 0; i < len; i++)
		{
			grid->Rows[0]->Cells[i]->Value = String::Format("[{0}]", i);
			grid->Rows[1]->Cells[i]->Value = mas[i].ToString("F3");
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

	// ЛР #3
	

	void Functions_Class::CreateAccessDbFile()
	{
		if (File::Exists(L"1dim_array.accdb"))
			File::Delete(L"1dim_array.accdb");

		ADOX::CatalogClass^ catalog = gcnew ADOX::CatalogClass();
		catalog->Create(ConnectionString);

		Marshal::FinalReleaseComObject(catalog->ActiveConnection);
		Marshal::FinalReleaseComObject(catalog);
	}

	void Functions_Class::CreateAccessDbTables()
	{
		OleDbConnection connection(ConnectionString);
		connection.Open();

		OleDbCommand command(LR"(
        CREATE TABLE [ИсходныйМассив] (
        [Id] LONG NOT NULL PRIMARY KEY,
        [Value] DOUBLE NOT NULL);)", % connection);

		command.ExecuteNonQuery();

		command.CommandText = LR"(
        CREATE TABLE [РезультирующийМассив] (
        [Id] LONG NOT NULL PRIMARY KEY,
        [Value] DOUBLE NOT NULL);)";

		command.ExecuteNonQuery();
	}

	void Functions_Class::FillAccessDb(double* sourceArray, double* transformedArray, int sourceArrayLength, int transformedArrayLength)
	{
		if (!File::Exists(L"1dim_array.accdb"))
			return;

		OleDbConnection connection(ConnectionString);
		connection.Open();

		OleDbCommand command(String::Empty, % connection);

		command.CommandText = L"DELETE FROM [ИсходныйМассив]";
		command.ExecuteNonQuery();

		for (int i = 0; i < sourceArrayLength; ++i)
		{
			command.CommandText = String::Format(LR"(
            INSERT INTO [ИсходныйМассив]
            ([Id], [Value]) VALUES
            ({0}, {1});)", i, sourceArray[i].ToString(CultureInfo::InvariantCulture));

			command.ExecuteNonQuery();
		}

		command.CommandText = L"DELETE FROM [РезультирующийМассив]";
		command.ExecuteNonQuery();

		for (int i = 0; i < transformedArrayLength; ++i)
		{
			command.CommandText = String::Format(LR"(
            INSERT INTO [РезультирующийМассив]
            ([Id], [Value]) VALUES
            ({0}, {1});)", i, transformedArray[i].ToString(CultureInfo::InvariantCulture));

			command.ExecuteNonQuery();
		}
	}

	

	void Functions_Class::FillWordDocument(const double* sourceArray, const double* transformedArray, const int sourceArrayLength, const int transformedArrayLength)
	{
		Object^ typeMissing = Type::Missing;
		Object^ wdWord9TableBehavior = Word::WdDefaultTableBehavior::wdWord9TableBehavior;
		Object^ wdAutoFitContent = Word::WdAutoFitBehavior::wdAutoFitContent;
		Object^ wdGoToLine = Word::WdGoToItem::wdGoToLine;
		Object^ wdGoToLast = Word::WdGoToDirection::wdGoToLast;

		auto wordApplication = gcnew Word::ApplicationClass();
		auto wordDocument = wordApplication->Documents->Add(typeMissing, typeMissing, typeMissing, typeMissing);

		wordDocument->PageSetup->Orientation = Word::WdOrientation::wdOrientLandscape;

		wordDocument->PageSetup->TopMargin = wordApplication->CentimetersToPoints(1.25);
		wordDocument->PageSetup->RightMargin = wordApplication->CentimetersToPoints(1.25);
		wordDocument->PageSetup->BottomMargin = wordApplication->CentimetersToPoints(1.25);
		wordDocument->PageSetup->LeftMargin = wordApplication->CentimetersToPoints(1.25);

		wordApplication->Selection->TypeText(L"Исходный массив:");
		wordApplication->Selection->TypeParagraph();

		auto wordTable = wordDocument->Tables->Add(wordApplication->Selection->Range, 2, sourceArrayLength, wdWord9TableBehavior, wdAutoFitContent);

		for (int i = 0; i < sourceArrayLength; ++i)
		{
			wordTable->Cell(1, i + 1)->Range->InsertAfter(String::Format(L"[{0}]", i));
			wordTable->Cell(2, i + 1)->Range->InsertAfter(sourceArray[i].ToString(L"F3"));
		}

		wordApplication->Selection->GoTo(wdGoToLine, wdGoToLast, typeMissing, typeMissing);
		wordApplication->Selection->TypeParagraph();
		wordApplication->Selection->TypeText(L"Результирующий массив:");
		wordApplication->Selection->TypeParagraph();

		wordTable = wordDocument->Tables->Add(wordApplication->Selection->Range, 2, transformedArrayLength, wdWord9TableBehavior, wdAutoFitContent);

		for (int i = 0; i < transformedArrayLength; ++i)
		{
			wordTable->Cell(1, i + 1)->Range->InsertAfter(String::Format(L"[{0}]", i));
			wordTable->Cell(2, i + 1)->Range->InsertAfter(transformedArray[i].ToString(L"F3"));
		}

		wordDocument->Content->Font->Name = L"Times New Roman";
		wordDocument->Content->Font->Size = 12;

		wordApplication->Selection->GoTo(wdGoToLine, wdGoToLast, typeMissing, typeMissing);
		try {
		Object^ filename = Path::Combine(Directory::GetCurrentDirectory(), L"1dim_array.docx");
		wordDocument->SaveAs(filename, typeMissing,
			typeMissing, typeMissing, typeMissing,
			typeMissing, typeMissing, typeMissing,
			typeMissing, typeMissing, typeMissing,
			typeMissing, typeMissing, typeMissing,
			typeMissing, typeMissing);

		
			wordApplication->Visible = true;
		}
		catch(Exception^ ex){
			
		}
	}

}