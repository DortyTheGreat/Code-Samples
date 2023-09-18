#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <queue>


using namespace std;

const int SZ = 10 * 1001;

/**
Íó çíà÷èò òîëüêî ÎÄÈÍ ÏÓÒÜ???
*/

int main()
{
    string name;
    cin >> name;
    map<char,int> req;

    for(const auto& c : name){
        req[c]++;
    }

    req['l']++;
    req['o']++;
    req['v']++;
    req['e']++;

    vector<pair<int,char>> pathes[SZ];





    int n,a,b;
    cin >> n >> a >> b;

    a--;
    b--;

    for(int i=0;i<n-1;++i){
        int l,r;
        char bukv;
        cin >> l >> r >> bukv;
        l--;
        r--;
        pathes[l].push_back({r,bukv});
        pathes[r].push_back({l,bukv});
    }

    int depths[SZ];
    pair<int,char> back_tracker[SZ];

    for(int i=0;i<SZ;++i){
        depths[i] = -1;
        back_tracker[i] = {-1,'Q'};
    }

    queue<int> awaiting_for_update;
    depths[a] = 0;
    back_tracker[a] = {-1337,'Q'};
    awaiting_for_update.push(a);

    bool RUN = true;

    while(!awaiting_for_update.empty() && RUN){
        int updating = awaiting_for_update.front();
        //cout << updating << endl;
        awaiting_for_update.pop();

        for(int j = 0; j < pathes[updating].size(); ++j){

            if (depths[pathes[updating][j].first] == -1){
                depths[pathes[updating][j].first] = depths[updating]+1;
                back_tracker[pathes[updating][j].first] = {updating, pathes[updating][j].second};
                awaiting_for_update.push(pathes[updating][j].first);
            }
            if (pathes[updating][j].first == b){
                RUN = false;
                break;
            }
        }
        pathes[updating].clear();

    }
    //cout << "finished main script" << endl;
    map<char,int> letters;
    int tracker = b;
    while(tracker != a){
        letters[back_tracker[tracker].second]++;
        tracker = back_tracker[tracker].first;
    }



    for(const auto& p : letters){
        //cout << p.first << " " << p.second << endl;
    }


    for(const auto& p : req){
        if (p.second > letters[p.first]){
            cout << "Fail"; return 0;
        }
    }

    cout << "Surprise"; return 0;

    return 0;
}
