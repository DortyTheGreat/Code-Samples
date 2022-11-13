#include <iostream>

using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;
    int x,y;
    cin >> x >> y;

    for(int i = 0;i<y;++i){
        cout << 'd';
    }

    for(int i = 0;i<x;++i){
        cout << 'r';
    }
    /// Можно пропустить, ибо мы не будем пользоваться информацией о втором яблоке cin >> x >> y;

    for(int i = 0;i<y+1;++i){
        cout << 'u';
    }

    return 0;
}
