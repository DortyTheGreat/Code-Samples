#include <iostream>

using namespace std;

/// Лепесток размером 2

struct Container{

    /// - это размер не этого контейнера, а число записанное на дуге к этому контейнеру, т.е. в частности если Arc_size = 0, то контейнер пустой(его нет)
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
