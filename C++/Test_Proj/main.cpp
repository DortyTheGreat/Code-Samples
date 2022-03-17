#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "argc : " << argc << endl;
    cout << "argv " << argv << endl;
    /// Project -> Build options -> вкладка Linker Settings -> Other linker options, там задаются все доп. настройки для линкера...
    /// Просто впечатай -static
    cout << "Hello world!" << endl;
    return 0;
}
