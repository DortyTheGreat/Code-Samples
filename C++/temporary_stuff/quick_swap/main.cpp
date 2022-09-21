#include <iostream>

#include <vector>

using namespace std;

void aboba(const vector<int>& v,const vector<int>& u){
    swap(*v,*u);
}

int main()
{
    vector<int> a,b;

    for(int i = 0;i<1000 * 1000; i++){
        a.push_back(rand() % 100);
        b.push_back(rand() % 100);
    }

    cout << a[0] << endl;

    cout << "pushed" << endl;

    for(int i = 0;i<1000 * 1000 + 1;i++){
        swap(a,b);
    }

    cout << a[0] << endl;

    cout << "Hello world!" << endl;
    return 0;
}
