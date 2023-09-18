#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<bool> > graph;
vector<int> colors; /// -1 none, 1 black, 0 white

int V;

/// обязательно должна быть хотя бы одна нода каждого цвета
bool force_alter_colors = 0;

bool reqursive(int src)
{
    colors[src] = (force_alter_colors ^= 1);

    queue <int> q;
    q.push(src);


    while (!q.empty())
    {

        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v)
        {
            if (!graph[u][v]) continue;
            if (colors[v] == -1)
            {
                colors[v] = 1 - colors[u];
                q.push(v);
            }

            else if (colors[v] == colors[u]) return false;
        }
    }
    return true;
}


// Driver program to test above function
int main()
{
    cin >> V;
    graph.resize(V);
    colors.resize(V);

    for(int i = 0; i < V; ++i){
        graph[i].resize(V);
        for(int j = 0; j < V; ++j){
            graph[i][j] = i != j;
        }
    }
    int E;
    cin >> E;
    for(int i = 0; i < E; ++i){
        int a,b;
        cin >> a >> b;
        --a;
        --b;
        graph[b][a] = graph[a][b] = 0;

    }

    for (int i = 0; i < V; ++i)
        colors[i] = -1;

    for (int i = 0; i < V; i++){
        if (colors[i] == -1){
            if (!reqursive(i)){
                cout << -1;
                return 0;
            }
        }
    }

    int k = 0;

    for(int i = 0; i < V; ++i){
        if (colors[i]){
            k++;
        }
    }

    cout << k << endl;

    for(int i = 0; i < V; ++i){
        if (colors[i]){
            cout << i+1 << " ";
        }
    }
    cout << endl;

    for(int i = 0; i < V; ++i){
        if (!colors[i]){
            cout << i+1 << " ";
        }
    }
    return 0;
}
