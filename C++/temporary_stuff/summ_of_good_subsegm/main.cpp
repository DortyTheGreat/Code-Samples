#include <iostream>
#include <set>
#define int long long

using namespace std;
const int size_ = 2 * 100000;
int arr[size_];
signed main()
{
    int n;
    cin >> n;


    multiset<int> ms;

    multiset<int> deleted;

    int summ = 0;
    for(int i = 0;i<n;++i){
        cin >> arr[i];
        summ += arr[i];
        ms.insert(summ);
    }
    summ = 0;
    for(int i = 0;i<n;++i){


        cout << "a : " << summ << " ";

        for (auto elem = ms.upper_bound(summ); elem != ms.end(); ++elem){
            cout << *elem << " ";
        }

        summ += arr[i];
        ms.erase(summ);
        cout << endl;
    }



    cout << "Hello world!" << endl;
    return 0;
}
