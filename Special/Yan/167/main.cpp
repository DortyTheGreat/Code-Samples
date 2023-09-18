#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

bool IsSquare(int number){
    return (int)(sqrt( abs(number))) == sqrt( abs(number));
}


map<int, vector<int > > cache;
vector<int> prefactored;
vector<int> all_divisers(int number){
    if (cache.find(number) != cache.end()) return cache[number];
    number = abs(number);
    vector<int> ans;
    int sqrt_= sqrt( number );
    for(int i = 0; i < prefactored.size(); ++i){
        if (prefactored[i] > number) break;
        if(number%prefactored[i]==0){ans.push_back(prefactored[i]);}
    }
    //for(int counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return cache[number] = ans;
}


vector<int> all_divisers_classic(int number){
    number = abs(number);
    vector<int> ans;
    int sqrt_= sqrt( number );
    for(int i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(int counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}




/// Раскладывает число на все возможные его представления в виде произведения чисел-1. (ака 12 = 3*2*2 (2 1 1), 12 = 4*3(3,2), 12 = 12(11),но, maxi отвечает за максимальный делитель, т.е. если maxi=10, то массив с числом  11 или больше не вернётся)
vector<vector<int>> All_Multes(int maxi_,int number)
{
    vector<vector<int>> returner;
    //if (number <= maxi_) returner.push_back({number});
    vector<int> ab = all_divisers(number);
    if (ab.size() == 2) {
        if (ab[1] <= maxi_){
            returner.push_back({ab[1]});
        }
        return returner;
    }

    for (int i = 1; i < (int)ab.size() && ab[i] <= maxi_; i++)
    {

        //cout << "abi : "<<ab[i] << endl;
        vector<vector<int>> the_rest = All_Multes(ab[i],number/ab[i]);
        for(uint32_t j = 0;j<the_rest.size();j++){
            ///the_rest[j].insert(the_rest[j].begin(),ab[i]);
            the_rest[j].push_back(ab[i]);
            //cout << ab[i] << " inserted" << endl;
            returner.push_back(the_rest[j]);
        }

        ///returner.insert(returner.begin(), ab[i])
    }

    return returner;
}

int main(){

    prefactored = all_divisers_classic(24);
    auto vcc = All_Multes(1001 * 1001 * 1001, 24);

    for(auto vc : vcc){
        for(auto elem : vc){
            cout << elem << " ";
        }
        cout << endl;
    }


    prefactored = all_divisers_classic(735134400);
    cout << All_Multes(1001 * 1001 * 1001, 735134400).size();

    auto elel = All_Multes(1001 * 1001 * 1001, 735134400);

    cout << elel.size() << endl;

    int big = 0;

    for(auto elelele : elel){
        big += elelele.size();
    }

    cout << big << endl;

    int n,m,k;
    /**
    cin >> n >> m >> k;
    vector<vector<int>>  vcc;

    cout << All_Multes(1001 * 1001 * 1001, 735134400).size();

    if (m != 0){
        vcc = All_Multes(1001 * 1001 * 1001, m);
    }
    map<int,int> mp;
    map<int, vector<int> > backtracker; /// number, indexes
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        mp[a]++;
        backtracker[a].push_back(i);
    }
    if (m == 0){
        int zeroindex = backtracker[0].back();
        int c = 1;

        cout << zeroindex+1 << " ";
        for(int i = 0; i < n; ++i){
            if (c == k) break;
            if (i != zeroindex){
                cout << i+1 << " ";
                ++c;
            }
        }
        return 0;
    }
    vcc.push_back({m});

    for(const auto& vc : vcc){

        for(const auto& elem : vc){
            //cout << elem << " ";
        }
        //cout << endl;

        int ones = k - vc.size() + (m == 1);
        if (ones < 0){
            continue;
        }

        map<int,int> mapified;
        for(const auto& elem : vc){
            mapified[elem]++;
        }

        bool flag = false;
        for(const auto& p : mapified){
            if (p.second > mp[p.first]){
                //cout << "failed in " << p.second << " " << p.first << " " << mp[p.first] << endl;
                flag = true;
                break;
            }
        }

        if (flag == false && mp[1] >= ones ){
            //cout << "suck" << endl;
            /// Ищем весь этот ужас и заканчиваем
            for(const auto& elem : vc){
                cout << backtracker[elem].back()+1 << " ";
                backtracker[elem].pop_back();
            }

            for(int i = 0; i < ones - (m == 1); ++i){
                cout << backtracker[1].back()+1 << " ";
                backtracker[1].pop_back();
            }

            return 0;
        }

    }
    */


}
