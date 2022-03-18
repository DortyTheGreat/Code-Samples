#include <iostream>

using namespace std;

int aboba(int arg,int n){
if (arg <= 0){
    return n + arg;
}

return arg;
}

int main()
{
    int n;
    cin >> n;

    if (n % 4 == 0){
        ///cout << n/0;
        cout << n-2 << endl;;

        for(int i =2;i<n/2 + 1;i++){
            cout << i <<" " << n-i + 2 << endl;
        }
        //cout << endl;
        int add = 0;
        if (n% 4 == 2){
            add =1;
        }
        for(int i =1;i<n/2;i++){
                int f = aboba(n/4 - i + 1 + add,n);
                int s = n/4 + i + 1 + add;
                if (f > s){
                    swap(f,s);
                }
            cout << f <<" " << s << endl;
        }

        return 0;
    }
    if (n%2 == 1){
        cout << n-3 << endl;
        for(int i =3;i<n;i++){
            cout << "1 " << i << endl;
        }
    }else{

        cout << n-2 << endl;
        for(int i =3;i<n;i++){
            cout << "1 " << i << endl;
        }

        cout << n/2 << " " << n/2 + 2<< endl;

    }

    return 0;
}
