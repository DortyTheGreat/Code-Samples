#include <iostream>

using namespace std;

/// �������� �������� 2

struct Container{

    /// - ��� ������ �� ����� ����������, � ����� ���������� �� ���� � ����� ����������, �.�. � ��������� ���� Arc_size = 0, �� ��������� ������(��� ���)
    int Arc_size = 0;

    Container* a;
    Container* b;
    Container(){
        a = 0;
        b = 0;
    }

};

int main()
{
    Container a;
    a.a = new Container();
    a.b = new Container();

    cout << a.b->Arc_size;

    cout << "Hello world!" << endl;
    return 0;
}
