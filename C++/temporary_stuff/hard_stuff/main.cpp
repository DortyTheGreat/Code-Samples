#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int size_ = 10005;
int main()
{
    vector<int> to[size_];
    bitset<32> masks[size_];

    bitset<32> ans[size_];


    for(int i = 0;i<size_;++i){
        masks[i] = 2147483647;
    }

    int n,q;
    cin >> n >> q;
    for(int i = 0;i<q;++i){
        int a,b,s;
        cin >> a >> b >> s;
        a--;
        b--;
        to[a].push_back(b);
        to[b].push_back(a);
        masks[a] &= s;
        masks[b] &= s;
    }
    for(int i = 0;i<n;++i){
        for(int bit = 31; bit>-1;--bit){
            if(masks[i][bit] == 0){
                ans[i][bit] = 0;
            }else{
                bool flag = 1;
                /// check if any of lower adjacent bits in masks is 1

                for(int c = 0; c < to[i].size();++c){
                    ///cout << "from " << i << " to " << to[i][c] << endl;
                    if ( ( (masks[to[i][c]][bit] == 0) )){
                        ///cout << "YES" << endl;
                        flag = 0;


                    }
                }
                if (flag == 0){
                    ans[i][bit] = 1;

                }else{


                    for(int c = 0; c < to[i].size();++c){
                        ///cout << "from " << i << " to " << to[i][c] << endl;
                        if ( ( (masks[to[i][c]][bit] == 1) && (to[i][c]>i) )){
                            ///cout << "YES" << endl;
                            flag = 0;


                        }
                        if ( ( (ans[to[i][c]][bit] == 1) && (to[i][c]<i) ) ){
                            ///ans[i][bit] = 1;
                            flag = 0;
                            break;
                        }
                    }


                    for(int c = 0; c < to[i].size();++c){
                        if ( ( (ans[to[i][c]][bit] == 0) && (to[i][c]<i) ) ){
                            ///ans[i][bit] = 1;
                            flag = 1;
                            break;
                        }
                    }



                    ans[i][bit] = flag;
                }
            }
        }
    }


    for(int i = 0;i<n;++i){
        ///cout << masks[i] << endl;
    }

    for(int i = 0;i<n;++i){
        int o = ans[i].to_ulong();
        if (o == 2147483647){
            cout << 0 << " ";
        }else{
            cout << o << " ";
        }
    }

    return 0;
}
