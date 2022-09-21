#include <iostream>

using namespace std;




int main()
{
    int deeta[100000];
    int h = 0;
    int n;
    cin >> n;

    for(int i = 0;i<n;i++){
        char r;
        cin >> r;
        if (r == '-'){
            ///...
            if (h == 1){
                cout << deeta[0] << endl;
            }else{
                cout << deeta[h-1] - deeta[h-2] << endl;
            }
            h--;
        }

        if (r == '+'){
            int a;
            cin >> a;

            if (h == 0){
                deeta[0] = a;
            }else{
                deeta[h] = deeta[h-1] + a;
            }
            h++;
        }

        if (r == '?'){
            int r;
            cin >> r;
            if ( (h - r - 1) == -1 ){
                cout << deeta[h-1] << endl;
            }else{
                cout << deeta[h-1] - deeta[h-r - 1] << endl;
            }

        }
    }

    return 0;
}
