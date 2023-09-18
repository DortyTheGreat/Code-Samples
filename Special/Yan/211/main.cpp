/**
Код вышел супер неэффективным, если что...
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector< map < string, vector< pair< pair<int,int>, vector<string> > > > > meetings_per_person (370);
/// ex. meetings_per_person[12]['john'] = { {(123,134), "Oleg, Dima, Egor"}, {(1234,1344), "Oleg1, Dima2, Egor3"}

bool check_collision(const pair<int,int>& period1,const pair<int,int>& period2){
    return (period1.first < period2.second) and (period1.second > period2.first);
}

bool check_ok(const string& name, int day, pair<int,int> period){

    for(auto elem : meetings_per_person[day][name]){
        if (check_collision(period, elem.first)) return false;
    }
    return true;
}

#include <iomanip>
int main()
{
    int n;
    cin >> n;
    while(n--){
        string r;
        cin >> r;
        if (r == "APPOINT"){
            int day, duration, k;
            string date;
            cin >> day >> date >> duration >> k;

            int minutes = stoi(date.substr(0,2)) * 60 +  stoi(date.substr(3,2));
            ///cout <<minutes << endl;

            vector<string> names(k);
            vector<string> names_invalid;
            for(int i =0; i < k; ++i){
                cin >> names[i];
                if ( ! check_ok(names[i], day, {minutes, minutes+duration} ) ){
                    names_invalid.push_back(names[i]);
                }
            }

            if (names_invalid.empty()){
                /// success, create appointment
                cout << "OK" << endl;
                for(int i =0; i < k; ++i){
                    //cout << meetings_per_person.size() << " " << day << endl;
                    if ( meetings_per_person[day].find(names[i]) == meetings_per_person[day].end()){
                        //cout << "hihi!";
                    }
                    meetings_per_person[day][names[i]].push_back( { {minutes, minutes+duration}, names } );
                }
            }else{
                /// error, throw it
                cout << "FAIL" << endl;
                for(int i = 0;i < names_invalid.size();++i){
                    cout << names_invalid[i] << " ";
                }
                cout << endl;
            }

            /// [minutes; minutes+duration)
        }else{
            int day;
            string name;
            cin >> day >> name;
            auto stuff = meetings_per_person[day][name];
            sort(stuff.begin(),stuff.end());
            for(auto elem : stuff){
                cout <<std::setfill('0') << std::setw(2)<< elem.first.first/60 << ":" <<std::setfill('0') << std::setw(2) <<elem.first.first%60 << " ";
                cout << elem.first.second - elem.first.first << " ";
                for(auto elem2 : elem.second){
                    cout << elem2 << " ";
                }
                cout << endl;
            }

        }
    }
    return 0;
}
