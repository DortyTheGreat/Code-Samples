#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ///setlocale (LC_ALL, "russian");
    string name;
    cout <<"��� ��� �����? " <<endl;
    getline(cin,name);
    string age;
    cout <<"������� ��� ���? " <<endl;
    getline(cin,age);
    string attitude;
    cout <<"����� ���� ��������� � ������ ����? " <<endl;
    getline(cin,attitude);
    string exam;
    cout <<"����� �������� �� ������� �� ���� ������? " <<endl;
    getline(cin,exam);
    string complexity;
    cout <<"��� ���� ������ ������� ��������? " <<endl;
    getline(cin,complexity);
    string grade;
    cout <<"����� ������ �� ��������? " <<endl;
    getline(cin,grade);
    string satis;
    cout <<"�������� �� �� ������ ��������? " <<endl;
    getline(cin,satis);
    cout <<" ����� ����� ����� ������, � ����������� ��� ��������� �������:"<<endl;

    ofstream s( (name) );

    s <<"1. ����������� ���� ������� �� ������ ����" << endl;
    s <<"2. �������� ������� ������� ����������� ��� �� ����� " << endl;
    s <<"3. �������� � ������������� ������ �������� � ��� � �������� �������" << endl;
    s <<"4. ��� ��������� �������, � �� � ��������� ����" << endl;
    s <<"5. ��������, ��� ���������� ��� ��� ���������� ���� ��������� ������� �������" << endl;
    s <<"6. ��� ������������� ������� ���� ����������" << endl;
    s <<"7. �������� ������������ ������" << endl;
    s <<"8. ����� ������ ������ (����, ����) � ��������� (������, ����� � �����)" << endl;
    s <<"9. ������� �������� ����� ����������� ������� ������� ����������" << endl;
    s <<"10. ���������� �����������" << endl;
    return 0;
}
