#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define int int64_t

signed main()
{

    ios::sync_with_stdio(0); cin.tie(0);
    int mod = 1000000007;
    int t;
    cin >> t;

    int l_vv[64];
    int h_vv[64];

    for(int x = 2; x < 63; ++x){


        l_vv[x] = floor(std::log(1ll << (x)) / std::log(x));

        h_vv[x] = floor(std::log((1ll << (x+1)) - 1ll) / std::log(x));
    }


    while(t--){
        int l, r;
        cin >> l >> r;

        int ans = 0;

        for(int x = 2; x < 63; ++x){

            int l_v = l_vv[x];

            int h_v = h_vv[x];

            ///cout << l_v << " " << h_v << endl;

            ///cout << std::log(1ll << (x)) / std::log(x) << " ";
            ///cout << std::log((1ll << (x+1)) - 1ll) / std::log(x);
            ///cout << endl;

            /// [2^x; 2^(x+1) - 1]



            if (l_v == h_v){

                int n_l = max(l,1ll << x);
                int n_r = min(r, (1ll << (x+1)) - 1);

                int intersection_size = max(n_r - n_l + 1,0ll);
                ///cout << "i_s" << intersection_size << endl;
                ans += l_v * intersection_size;
                ans %= mod;
                ///cout << x << endl;
            }else{
                /// bruh...
                /// log_x(idk) = h_v
                /// <=> idk = x^h_v

                int idk = 1;

                for(int i=0;i < h_v; ++i){
                    idk *= x;
                }

                --idk;


                /// [2^x; idk] - l_v, [idk+1, rest] - h_v

                ///cout << x << " " << (1ll << (x)) <<" "<< idk << " " << (1ll << (x+1))-1 << endl;

                int n_l = max(l,1ll << x);
                int n_r = min(r, idk);

                int intersection_size = max(n_r - n_l + 1,0ll);
                ///cout << "i_s: " << intersection_size << endl;
                ans += l_v * intersection_size;
                ans %= mod;



                n_l = max(l,idk + 1);
                n_r = min(r, (1ll << (x+1)) - 1);

                intersection_size = max(n_r - n_l + 1,0ll);
                ///cout << "i_s: " << intersection_size << endl;
                ans += h_v * intersection_size;
                ans %= mod;

            }


            ///cout << ans << " " << x << endl;



        }

        cout << ans << "\n";


    }

    return 0;
}
