#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct sotr{
    vector<int> uprav;
    int cost;
};

map<int, sotr> company;

int get_cost(int id){
    int total = 0;
    if (company[id].uprav.size() == 0){return company[id].cost;}

    for(int i = 0; i < company[id].uprav.size(); ++i){
        total += get_cost(company[id].uprav[i]);
    }

    return total;
}

int main()
{

    company[0] = { {},0 };



    int Q;
    cin >> Q;

    for(int i = 0; i < Q; ++i){
        string r;
        cin >> r;
        if (r == "add"){
            int id, parent_id, cost;
            cin >> id >> parent_id >> cost;
            company[id] = { {}, cost};
            company[parent_id].uprav.push_back(id);
        }

        if (r == "check"){
            int id, parent_id, cost;
            cin >> id;
            cout << get_cost(id) << " ";
        }
    }


    return 0;
}
