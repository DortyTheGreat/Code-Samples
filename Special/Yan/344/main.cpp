#include <iostream>
#include <vector>
using namespace std;

struct Checkers{
    /// 0 - empty, 1 - white, -1 - black
    vector< vector< int > > field;
    int n,m;

    Checkers(int _n, int _m, int elem = 0){
        n = _n;
        m = _m;
        field.resize(n);
        for(int i = 0; i < n; ++i){
            field[i].resize(m);
            for(int j = 0; j < m; ++j){
                field[i][j] = elem;
            }
        }
    }

    bool isValid(int x, int y){
        return !(x >= n || y >= m || x < 0 || y < 0);
    }

    bool isBlack(int x, int y){
        if (!isValid(x,y)) return false;
        return field[x][y] == -1;
    }

    bool isWhite(int x, int y){
        if (!isValid(x,y)) return false;
        return field[x][y] == 1;
    }

    bool isEmpty(int x, int y){
        if (!isValid(x,y)) return false;
        return field[x][y] == 0;
    }

};

int main()
{
    int n,m;
    cin >> n >> m;
    Checkers ck(n,m);

    int w;
    cin >> w;
    for(int i = 0; i < w; ++i){
        int a,b;
        cin >> a >> b;
        ck.field[a-1][b-1] = 1;
    }

    int b;
    cin >> b;
    for(int i = 0; i < b; ++i){
        int a,b;
        cin >> a >> b;
        ck.field[a-1][b-1] = -1;
    }


    /// Супер тупо, но пофигу -_-
    string color;
    cin >> color;

    if (color == "white"){
        for(int x = -2; x < 1005; ++x){
            for(int y = -2; y < 1005; ++y){

                if (ck.isWhite(x,y) && ck.isBlack(x+1,y+1) && ck.isEmpty(x+2,y+2)){
                    cout << "Yes";
                    return 0;
                }

                if (ck.isWhite(x,y) && ck.isBlack(x-1,y+1) && ck.isEmpty(x-2,y+2)){
                    cout << "Yes";
                    return 0;
                }

                if (ck.isWhite(x,y) && ck.isBlack(x+1,y-1) && ck.isEmpty(x+2,y-2)){
                    cout << "Yes";
                    return 0;
                }

                if (ck.isWhite(x,y) && ck.isBlack(x-1,y-1) && ck.isEmpty(x-2,y-2)){
                    cout << "Yes";
                    return 0;
                }

            }
        }
    }else{

        for(int x = -2; x < 1005; ++x){
            for(int y = -2; y < 1005; ++y){

                if (ck.isBlack(x,y) && ck.isWhite(x+1,y+1) && ck.isEmpty(x+2,y+2)){
                    cout << "Yes";
                    return 0;
                }

                if (ck.isBlack(x,y) && ck.isWhite(x-1,y+1) && ck.isEmpty(x-2,y+2)){
                    cout << "Yes";
                    return 0;
                }

                if (ck.isBlack(x,y) && ck.isWhite(x+1,y-1) && ck.isEmpty(x+2,y-2)){
                    cout << "Yes";
                    return 0;
                }

                if (ck.isBlack(x,y) && ck.isWhite(x-1,y-1) && ck.isEmpty(x-2,y-2)){
                    cout << "Yes";
                    return 0;
                }

            }
        }


    }


    cout << "No";

    return 0;
}
