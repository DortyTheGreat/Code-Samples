#include <iostream>
#include <vector>
using namespace std;
#define int long long
signed main()
{
    int t;

    int h;

    cin >> t;
    while(t--){
        int n, x,y;
        cin >> n >> x >> y;
        string a,b;
        bool c[10000];
        cin >> a >> b;

        int diff = 0;
        for(int i = 0;i<n;i++){
            c[i] = !(a[i] == b[i]);
            diff += !(a[i] == b[i]);
        }

        if (diff % 2 == 1){
            cout << -1 << endl;
            continue;
        }

        if (diff == 0){
            cout << 0 << endl;
            continue;
        }

        if (x >= y){

            if (diff > 2){
                cout << diff/2 *  y << endl;
                continue;
            }

            if (diff == 2){
                bool flag = 1;
                for(int i = 0;i<n-1;i++){
                    if ( (c[i]==1)&&(c[i+1] == 1) ){

                        if (n <= 3){
                            cout << x;
                            flag = 0;
                        }
                        if (n == 4){

                            if (i == 1){

                                cout << min(3*y,x) << endl;
                                flag = 0;

                                /// 3 long
                            }else{
                                cout << min(2*y,x) << endl;
                                flag = 0;
                            }

                        }

                        if (n >= 5){
                            cout << min(2*y,x) << endl;
                            flag = 0;

                        }


                    }
                }

                if (flag) cout << y << endl;
                continue;
            }

        }else{
            vector<int> clusters;
            clusters.push_back(0);
            int in_1 = 0;
            for(int i = 0;i<n;i++){
                if (in_1==0 && c[i] == 0 ) continue;
                if (in_1==1 && c[i] == 0){
                    clusters.push_back(0);
                    in_1 = 0;
                }



                if (c[i] == 1){
                    clusters.back()++;
                    in_1 = 1;
                }
            }
            int s = 0;
            for(int i =0;i<clusters.size();++i){
                s += 2*x*(clusters[i]/2) + y*((clusters[i]%2));
            }
            s /= 2;
            cout << s << endl;



        }


    }


    return 0;
}
