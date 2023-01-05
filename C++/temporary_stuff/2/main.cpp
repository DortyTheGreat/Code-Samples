#include <iostream>
#include <utility>
#include <set>
#include <vector>
using namespace std;

int main()
{
    int n,k;
    vector<int> table[20];
    cin >> n >> k;
    /// time at finish, his ID

    multiset<pair<int,int > > humans;

    for(int i = 0;i<k;i++){
        humans.insert({0,i});
    }

    /// time left to start, time that it will take , id
    multiset<pair<int,pair<int,int> > > tasks;

    for(int i = 0;i<n;i++){
        int t,d;
        cin >> t >> d;
        tasks.insert({d-t,{t, i+1}});
    }

    int time = 0;

    while(1){
        if ( tasks.empty()){
            cout << "YES" << endl;
            for(int i = 0;i<k;i++){
                cout << table[i].size() << " ";
                for(int j = 0;j<table[i].size();j++){
                    cout << table[i][j] << " ";
                }
                cout << endl;
            }
            break;
        }
        auto first_item = *(tasks.begin());
        auto first_human = *(humans.begin());
        if ( first_human.first > first_item.first ){
            cout << "NO" << endl;
            return 0;
        }


        table[first_human.second].push_back(first_item.second.second);

        (humans.begin())->first += first_item.second.first;

        tasks.erase(tasks.begin());
    }

    return 0;
}
