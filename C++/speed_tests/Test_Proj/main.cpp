#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "argc : " << argc << endl;
    cout << "argv " << argv << endl;
    /// Project -> Build options -> ������� Linker Settings -> Other linker options, ��� �������� ��� ���. ��������� ��� �������...
    /// ������ �������� -static
    cout << "Hello world!" << endl;
    return 0;
}
