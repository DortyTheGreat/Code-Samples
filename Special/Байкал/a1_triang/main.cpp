#include <iostream>
#include <queue>
#include <set>

using namespace std;

int MAXN = 3 * 100 * 11;

int main()
{

    int n,m;
    cin >> n >> m;
    vector<int> roads[MAXN];
    for(int i =0;i < m; ++i){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        roads[a].push_back(b);
        roads[b].push_back(a);
    }

    int ans = 0;

    int colors[MAXN];
    int depth[MAXN];

    queue<int> awaiting_for_update;

    for(int i =0;i<MAXN; ++i){
        colors[i] = 0;
    }


    int color_cou = 1;


    set<int> non_visited;

    for(int i = 0; i < n; ++i){
        non_visited.insert(i);
    }


    while(!non_visited.empty()){
        awaiting_for_update.push(*non_visited.begin());
        colors[*non_visited.begin()] = color_cou;
        color_cou++;

        while(!awaiting_for_update.empty()){

            int updating = awaiting_for_update.front();
            awaiting_for_update.pop();
            non_visited.erase(updating);
            //cout << s_node<<" : " << updating << endl;

            for(int j = 0; j < roads[updating].size(); ++j){

                //cout <<"in: " << updating <<" "<<roads[updating][j] << endl;
                //cout <<"cl: " << colors[updating] <<" "<<colors[roads[updating][j]] << endl;

                if (colors[roads[updating][j]] != 0){

                    if(colors[updating] < colors[roads[updating][j]]){
                        //cout << "+1" << endl;
                        ans += 1;
                    }

                    continue;
                }

                if (colors[roads[updating][j]] == 0){
                    colors[roads[updating][j]] = color_cou; /// даёт такой же цвет...
                    color_cou++;
                    awaiting_for_update.push(roads[updating][j]);
                    continue;
                }



            }
            roads[updating].clear();



        }
    }




    cout << ans << endl;


    return 0;
}
