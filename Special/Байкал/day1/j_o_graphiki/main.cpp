#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        vector<int> roads[300];
        for(int i =0;i < m; ++i){
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            roads[a].push_back(b);
            roads[b].push_back(a);
        }

        int ans = 99999;

        for(int s_node = 0; s_node < n; ++s_node){

            int colors[300];
            int depth[300];

            queue<int> awaiting_for_update;

            for(int i =0;i<300; ++i){
                colors[i] = 0;
                depth[i] = -1;
            }

            colors[s_node] = -1;
            depth[s_node] = 0;

            for(int j = 0; j < roads[s_node].size(); ++j){
                colors[roads[s_node][j]] = j+1;
                depth[roads[s_node][j]] = 1;
                awaiting_for_update.push(roads[s_node][j]);
            }

            ///roads[s_node].clear();

            bool populating = true;
            while(!awaiting_for_update.empty()){

                int updating = awaiting_for_update.front();
                awaiting_for_update.pop();
                //cout << s_node<<" : " << updating << endl;

                for(int j = 0; j < roads[updating].size(); ++j){
                    //cout << "> " << roads[updating][j] << endl;
                    if (colors[roads[updating][j]] == -1){
                        continue; /// ничего не делаем, ибо это "глава"
                    }

                    if (colors[roads[updating][j]] == 0){
                        colors[roads[updating][j]] = colors[updating]; /// даёт такой же цвет...
                        if (populating) depth[roads[updating][j]] = depth[updating]+1;
                        awaiting_for_update.push(roads[updating][j]);
                        continue;
                    }

                    if (colors[roads[updating][j]] == colors[updating]){
                        continue; /// ничего не делаем, уже были также заражены
                    }

                    if (colors[roads[updating][j]] != colors[updating]){
                        /// БИТВА ЦВЕТОВ! МЫ БЛИЗКИ
                        ans = min(ans,depth[updating] + depth[roads[updating][j]]);
                        //populating = false;
                        continue;
                    }



                }
                ///roads[s_node].clear();



            }



        }
        cout << ans+1 << endl;
    }

    return 0;
}
