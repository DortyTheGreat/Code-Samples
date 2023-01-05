#include <iostream>
#include <set>
#include <map>
using namespace std;

struct deeta{
    int minutes, id;
    char status;
    /*
    deeta(int m, int i, char s){
        minutes = m;
        id = i;
        status = s;
    }

    deeta(const deeta&) = default;
    */
    bool operator<(const deeta& other) const{
        return minutes < other.minutes;
    }
};

int main()
{
    int n;
    cin >> n;
    multiset<deeta> st;
    for(int i = 0; i < n;++i){
        int a,b,c,id;
        char status;
        cin >> a >> b >> c >> id >> status;
        int minutes = a*24*60 + b*60 + c;
        deeta f = {minutes, id, status};
        ///cout << f.minutes << endl;
        st.insert(f);

    }

    map<int, deeta> rockets; /// id, rocket

    map<int, long long> times; /// id, time

    for(deeta that : st){
        ///cout << "G " << that.minutes << " " << that.id << " " << that.status << endl;
        auto itter = rockets.find(that.id);
        if (itter == rockets.end()){
            /// нет такой ракеты в моём логе => добавь её
            rockets[that.id] = that;
            continue;
        }

        if (that.status == 'A'){
            rockets[that.id] = that;
        }

        if (that.status == 'S' || that.status == 'C'){
            times[that.id] += (that.minutes - rockets[that.id].minutes);
            ///cout << "S  " << that.minutes << " " << rockets[that.id].minutes << " " << that.id << endl;
        }
    }


    for(const auto& p : times){
        cout << p.second << " ";
    }
    return 0;
}
