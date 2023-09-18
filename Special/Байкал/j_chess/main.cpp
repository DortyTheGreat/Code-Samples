#include <bits/stdc++.h>

using namespace std;

int main(){
    cout << "? c4" << endl;
    bool t, i;
    cin >> t;
    if(t){ // queen | slon
        cout << "? c2" << endl;
        cin >> t;
        cout << "? e2" << endl;
        cin >> i;
        if (t) {
                cout << "! q";
        }
        else{
                cout << "! b";
        }
    }
    else{ // kon king ladya pesh
        cout << "? f2" << endl;
        cin >> t;
        if(t){ // king ladya
            cout << "? e3" << endl;
            cin>>t;
            cout << "? e2" << endl;
            cin >> i;
            if(t){ // king
                cout << "! k";
            }
            else{//ladya
                cout << "! r";
            }
        }
        else{ // pesh kon
            cout << "? e3" << endl;
            cin >> t;
            if(t){//pesh
                cout << "? e2" << endl;
                cin >> i;
                cout << "! p";
            }
            else{ //kon
                cout << "! n";
            }
        }
    }
    return 0;
}
