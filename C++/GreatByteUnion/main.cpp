#include <iostream>
#include <set>
#include <utility>
using namespace std;



int main()
{
    multiset<pair<int,int>,greater<pair<int,int> > > a;
    /// cost, orig_city

    int n;
    cin >> n;
    const int sz = 200000;
    int arr[sz];

    for(int i = 0;i<sz;i++){
        arr[i] = -1;
    }

    for(int i = 0;i<n;i++){
        int num;
        cin >> num;

        a.insert({num,i});
        /// Удалить все, которые больше 4
        auto it = a.begin();
        for(; it != a.end(); ++it){
            if ((*it).first <= num){
                break;
            }else{
                arr[(*it).second] = i;
            }
        }
        a.erase(a.begin(), it);

    }



    for(int i = 0;i<n;i++){
        cout << arr[i] << " ";
    }


    return 0;
}
