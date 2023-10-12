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
		if (File::Exists("1dim_array.accdb"))
			File::Delete("1dim_array.accdb");

		ADOX::CatalogClass^ catalog = gcnew ADOX::CatalogClass();
		catalog->Create(ConnectionString);

		Marshal::FinalReleaseComObject(catalog->ActiveConnection);
		Marshal::FinalReleaseComObject(catalog);
	}

	void Functions_Class::CreateAccessDbTables()
	{
		OleDbConnection connection(ConnectionString);
		connection.Open();

		OleDbCommand command(R"(
        CREATE TABLE [SourceArray] (
        [Id] LONG NOT NULL PRIMARY KEY,
        [Value] DOUBLE NOT NULL);)", % connection);

		command.ExecuteNonQuery();

		command.CommandText = R"(
        CREATE TABLE [TransformedArray] (
        [Id] LONG NOT NULL PRIMARY KEY,
        [Value] DOUBLE NOT NULL);)";

		command.ExecuteNonQuery();
	}

	void Functions_Class::FillAccessDb(const double* sourceArray, const double* transformedArray, int sourceArrayLength, int transformedArrayLength)
	{
		if (!File::Exists("1dim_array.accdb"))
			return;

		OleDbConnection connection(ConnectionString);
		connection.Open();

		OleDbCommand command(String::Empty, % connection);

		command.CommandText = "DELETE FROM [SourceArray]";
		command.ExecuteNonQuery();

		for (int i = 0; i < sourceArrayLength; ++i)
		{
			command.CommandText = String::Format(R"(
            INSERT INTO [SourceArray]
            ([Id], [Value]) VALUES
            ({0}, {1});)", i, sourceArray[i]);

			command.ExecuteNonQuery();
		}

		command.CommandText = "DELETE FROM [TransformedArray]";
		command.ExecuteNonQuery();

		for (int i = 0; i < transformedArrayLength; ++i)
		{
			command.CommandText = String::Format(R"(
            INSERT INTO [TransformedArray]
            ([Id], [Value]) VALUES
            ({0}, {1});)", i, transformedArray[i]);

			command.ExecuteNonQuery();
		}
	}
}