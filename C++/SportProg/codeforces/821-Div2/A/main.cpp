#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long

int sign(int a){
    if (a < 0) return -1;
    if (a > 0) return 1;
    return 0;
}

#define sz 2007
signed main()
{
    int t;
    int arr[sz];
    int new_arr[sz];
    pair<int,int> fwd[sz]; /// incr, requirement
    pair<int,int> bckd[sz]; /// incr, requirement
    cin >> t;
    while(t--){
        int n,k;
        int h = 0;
        int fw = 0;
        int bc = 0;

        cin >> n >> k;
        int new_k = 0;
        --k;
        for(int i = 0;i<n;++i){
            cin >> arr[i+1];
        }
        if (k == 0 || k == n-1){cout << "YES" << endl; continue;}
        arr[0] = 1e16;
        arr[n+1] = 1e16;
        n += 2;
        new_arr[h++] = arr[0];
        for(int i = 1;i<n;++i){
            if (sign(new_arr[h-1]) == sign(arr[i]) ){
                new_arr[h-1] += arr[i];
            }else{
                new_arr[h++] = arr[i];
            }
            if ( (i-1) == k){
                new_k = h - 1;
            }
        }

        cout << endl;
        for(int i = 0;i<h;++i){
            cout << new_arr[i] << " ";
        }
        cout << endl<<"k= " << new_k << endl;




        cout << "forward: ";

        bool isCreated = false;

        for(int i = new_k+1;i<h;i+=2){

            if (!isCreated){
                fwd[fw] = {abs(new_arr[i]), new_arr[i+1] + new_arr[i] };

            }else{

                fwd[fw].first = max(fwd[fw].first, abs(new_arr[i]) - fwd[fw].second);
                fwd[fw].second += new_arr[i+1] + new_arr[i];
            }


            if (fwd[fw].second >= 0){
                isCreated = false;
                fw++;
            }else{
                isCreated = true;
            }

        }

        for(int i = 0;i < fw;++i){
            cout << "(" << fwd[i].first << " " << fwd[i].second << ") ";
        }

        cout << endl;

        cout << "backward: ";

        isCreated = false;
        for(int i = new_k-1;i>-1;i-=2){

            if (!isCreated){
                bckd[bc] = {abs(new_arr[i]), new_arr[i-1] + new_arr[i] };

            }else{

                bckd[bc].first = max(bckd[bc].first, abs(new_arr[i]) - bckd[bc].second);
                bckd[bc].second += new_arr[i-1] + new_arr[i];
            }


            if (bckd[bc].second >= 0){
                isCreated = false;
                bc++;
            }else{
                isCreated = true;
            }

        }


        for(int i = 0;i < bc;++i){
            cout << "(" << bckd[i].first << " " << bckd[i].second << ") ";
        }



        int value = new_arr[new_k];


        int carB = 0,carF = 0;
        while(1){

            if (carB == bc){cout << "YES" << endl; break;}
            if (carF == fw){cout << "YES" << endl; break;}

            if (bckd[carB].first <= value){
                value += bckd[carB].second;
                carB++;
                continue;
            }

            if (fwd[carF].first <= value){
                value += fwd[carF].second;
                carF++;
                continue;
            }

            cout << "NO" << endl;
            break;


        }

        cout << endl;





    }


    return 0;
}
