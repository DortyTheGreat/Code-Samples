#include <iostream>

using namespace std;

class Big_class{
public:
    int mem[10000];
};

void a(Big_class obj){
    obj.mem[rand() % 10000]++;
}

int main()
{
    Big_class r;

    for(int i = 0;i<10000;i++){
        r.mem[i] = 0;
    }

    for(int i = 0; i < 1000 * 1000; ++i){
        a(r);
    }

    /**
    class (size 10k x 1 mil) - 1.246 s

    Аналогично для struct

    Смысл в том, что cpp создаёт копию класса, он никак не меняет основной объект, а чистое(aka прямое) копирование памяти быстрее,
    чем

    */

    cout << "Hello world!" << endl;
    return 0;
}
