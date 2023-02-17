#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;
#define int long long
const int maxn = 2 * 100006;

const int INF = 1000 * 1000 * 1000;

int a[maxn];

int extra_bits[maxn];

int b[maxn];

signed main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i =0;i<n+3;++i){
            extra_bits[i] = 0;
        }

        int summ = 0;
        vector<int> summa_a;

        for(int i = 0;i<n;++i){
            cin >> b[i];
        }

        for(int i = 0;i<n;++i){
            cin >> a[i];
            summ += a[i];
            summa_a.push_back(summ);
        }


        multiset<int> starts;
        multiset<int> ends;

        int a_s = 0;
        for(int i = 0; i < n;++i){
            auto it = upper_bound(summa_a.begin(),summa_a.end(),a_s + b[i]  );
            //cout << "POINTING TO: " << (*it) << endl;
            /// этот чай могут выпить все
            if (it == summa_a.end()){
                //cout << "all" << endl << endl;
                starts.insert(i); // начиная с i
                ends.insert(INF);
                a_s += a[i];
                continue;
            }

            if (it == summa_a.begin()){
                extra_bits[i] += b[i]; /// В одно рыло.
                a_s += a[i];
                continue;
            }


            starts.insert(i); // начиная с i
            //cout << "S: " << i << endl;
            ends.insert(it - summa_a.begin());
            //cout << "ENDS: " << std::distance(summa_a.begin(), it) + i << endl;
            extra_bits[it - summa_a.begin() +1] += b[i] - (*(--it)) + a_s;
            //cout << "EXTRA: " << b[i] - (*(it)) << endl;

            //cout << "EXTRA ID: " << std::distance(summa_a.begin(), it) +1 << endl;

            //cout << "found: " << (*it) << " as " << a_s + b[i] << endl;
            //cout <<"D: " <<std::distance(summa_a.begin(), it) << endl;
            a_s += a[i];


        }

        int curret = 0;
        for(int i = 0;i < n;++i){
            int v = 0;
            if (!ends.empty()){
                while( *(ends.begin()) == i ){
                    curret -= 1;
                    ends.erase(ends.begin());
                    if (ends.empty()){
                        break;
                    }
                }
            }

            if (!starts.empty()){
                    while( *(starts.begin()) == i ){
                        curret += 1;
                        starts.erase(starts.begin());
                        if (starts.empty()){
                            break;
                        }
                    }
                }

            cout << curret*a[i]+extra_bits[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
