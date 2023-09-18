#include <iostream>
#include <ctime>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int day;
    string month;
    int year;

    vector<string> vc = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    map<string,int> mp;
    /// January, February, March, April, May, June, July, August, September, October, November, and December
    mp.insert({"January",1});
    mp.insert({"February",2});
    mp.insert({"March",3});
    mp.insert({"April",4});
    mp.insert({"May",5});
    mp.insert({"June",6});
    mp.insert({"July",7});
    mp.insert({"August",8});
    mp.insert({"September",9});
    mp.insert({"October",10});
    mp.insert({"November",11});
    mp.insert({"December",12});


    while(cin >> day >> month >> year){

        std::tm date={};
        date.tm_year=year-1900;


        date.tm_mon=mp[month]-1;
        date.tm_mday=day;
        std::mktime(&date);



        cout << vc[date.tm_wday] <<endl;
    }

    return 0;
}
