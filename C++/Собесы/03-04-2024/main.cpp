#include <iostream>
#include <set>
#include <utility>
#include <map>

using namespace std;

pair<int,int> operator+ (pair<int,int> a, pair<int,int> b){
    return {a.first+b.first, a.second+b.second};
}

int check(pair<int,int> pa, map<pair<int,int>, int >& st, int state){
    /// Это не красиво, на работает :-)

    /// я даже знаю адекватное решение с массивами dx, но хи-хи!


    int Tx = 0;

    for(int i = 1; ; ++i){
        if (st[pa+make_pair(0,i)] == state) Tx++;
        else break;
    }
    for(int i = 1; ; ++i){
        if (st[pa+make_pair(0,-i)] == state) Tx++;
        else break;
    }

    if (Tx >= 4) return 1;
    Tx = 0;

    for(int i = 1; ; ++i){
        if (st[pa+make_pair(i,0)] == state) Tx++;
        else break;
    }

    for(int i = 1; ; ++i){
        if (st[pa+make_pair(-i,0)] == state) Tx++;
        else break;
    }

    if (Tx >= 4) return 1;
    Tx = 0;


    for(int i = 1; ; ++i){
        if (st[pa+make_pair(i,i)] == state) Tx++;
        else break;
    }

    for(int i = 1; ; ++i){
        if (st[pa+make_pair(-i,-i)] == state) Tx++;
        else break;
    }

    if (Tx >= 4) return 1;
    Tx = 0;

    for(int i = 1; ; ++i){
        if (st[pa+make_pair(i,-i)] == state) Tx++;
        else break;
    }

    for(int i = 1; ; ++i){
        if (st[pa+make_pair(-i,i)] == state) Tx++;
        else break;
    }

    if (Tx >= 4) return 1;




    return 0;
}

int main()
{

    map<pair<int,int>, int > board;

    int n;
    cin >> n;

    for(int i = 0; i < n; ++i){
        int a,b;
        cin >> a >> b;
        board[{a,b}] = (i%2) + 100;
        int st = check({a,b},board, (i%2) + 100);
        if (st != 0){
            if (i == (n - 1)){
                if (!(i % 2)){
                    cout << "First";
                    return 0;
                }else{
                    cout << "Second";
                    return 0;
                }
            }else{
                cout << "Inattention";
                return 0;
            }
        }
    }
    cout << "Draw" << endl;
    return 0;
}
