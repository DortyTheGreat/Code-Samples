#include <iostream>
#include <set>

#define int long long

using namespace std;
const int size_ = 40000;///400000
signed main()
{

    int arr[size_];
    int help[size_];

    multiset<int> MS;

    int t;
    cin >> t;
    for(int itter = 0;itter<t;itter++){
        int n;
        cin >> n;
        MS.clear();

        cin >> arr[0];
        help[0] = arr[0];
        MS.insert(help[0]);

        for(int i = 1;i<n;i++){
            cin >> arr[i];
            if ( !(i%2)){
                help[i] = help[i-1] + arr[i];
            }else{
                help[i] = help[i-1] - arr[i];
            }
            MS.insert(help[i]);
        }


        for(int i = 0;i<n;i++){
            //cout << help[i] << " ";
        }

        //cout << endl;

        int ans = 0;
        int find_ = 0;
        for(int i =0;i<n;i++){
            ans += MS.count(find_);
            MS.erase(MS.find(help[i]));
            find_ = help[i];
            //cout << ans << " ";
        }

        //cout << endl;

        cout << ans << endl;


    }
    return 0;
}
