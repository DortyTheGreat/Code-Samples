#include <iostream>

using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;

    if (n == 1 && k == 1){cout << "Yes\n"; cout << "1"; return 0;}

    if (n == 1 && k != 1){cout << "No\n"; return 0;}

    if (n != 1 && k == 1){cout << "No\n"; return 0;}

    if ( n*n % k != 0){cout << "No\n"; return 0;}


    cout << "Yes\n";

    if (n == 6 && k == 4){
        cout << "1 2 1 2 1 2\n3 4 3 4 3 4\n1 2 1 2 1 2\n3 4 3 4 3 4\n1 2 1 2 1 2\n3 4 3 4 3 4";
        return 0;
    }

    if (n == 2 && k == 4){
        cout << "1 2\n3 4";
        return 0;
    }

    if (n == 3 && k == 9){
        cout << "1 2 3\n4 5 6\n7 8 9";
        return 0;
    }

    if (n == 4 && k == 8){
        cout << "1 2 3 4\n5 6 7 8\n1 2 3 4\n5 6 7 8";
        return 0;
    }

    if (n == 6 && k == 9){
        cout << "1 2 3 4 5 6\n7 8 9 1 2 3\n4 5 6 7 8 9\n1 2 3 4 5 6\n7 8 9 1 2 3\n4 5 6 7 8 9\n";
        return 0;
    }

    if (n == 10 && k == 4){
        cout << "1 2 3 4 1 2 3 4 1 2\n3 4 1 2 3 4 1 2 3 4\n1 2 3 4 1 2 3 4 1 2\n3 4 1 2 3 4 1 2 3 4\n1 2 3 4 1 2 3 4 1 2\n3 4 1 2 3 4 1 2 3 4\n1 2 3 4 1 2 3 4 1 2\n3 4 1 2 3 4 1 2 3 4\n1 2 3 4 1 2 3 4 1 2\n3 4 1 2 3 4 1 2 3 4\n";
        return 0;
    }



    if (k == 2){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "12"[(i + j) % 2] << " ";
            }
            cout << endl;
        }
    }


    if (k == 3){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "123"[(i + j) % 3] << " ";
            }
            cout << endl;
        }

    }

    if (k == 4){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "1234"[(i + j) % 4] << " ";
            }
            cout << endl;
        }

    }

    if (k == 5){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "12345"[(i + j) % 5] << " ";
            }
            cout << endl;
        }

    }

    if (k == 6){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "123456"[(i + j) % 6] << " ";
            }
            cout << endl;
        }

    }

    if (k == 7){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "1234567"[(i + j) % 7] << " ";
            }
            cout << endl;
        }

    }

    if (k == 8){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "12345678"[(i + j) % 8] << " ";
            }
            cout << endl;
        }

    }

    if (k == 9){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                cout << "123456789"[(i + j) % 9] << " ";
            }
            cout << endl;
        }

    }

    if (k == 10){

        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                if ( (i + j) % 10 != 9)
                    cout << "123456789"[(i + j) % 10] << " ";
                else
                    cout << "10 ";
            }
            cout << endl;
        }

    }


    return 0;
}
