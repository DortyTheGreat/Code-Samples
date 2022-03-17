#include <iostream>
#include <vector>
#include <set>


using namespace std;

struct Node{
    int parent_index = -2;
    int time = 0;
    bool working = false;
};


int main()
{
    vector<Node> nodes;
    int n,m;
    cin >> n >> m;
    nodes.resize(n);

    nodes[0].working = true;
    nodes[0].parent_index = -1;

    for(int time = 1;time<=m;time++){
        char type;
        cin >> type;
        if (type == '!'){
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            nodes[b].parent_index = a;
            nodes[b].working = true;
            nodes[b].time = time;
        }

        if (type == '-'){
            int a;
            cin >> a;
            a--;
            nodes[a].working = false;
        }

        if (type == '+'){
            int a;
            cin >> a;
            a--;
            nodes[a].working = true;
            nodes[a].time = time;
        }

        if (type == '?'){
            int a,b;
            cin >> a >> b;
            a--;
            b--;

            if ( (nodes[a].parent_index > -2) && (nodes[b].parent_index > -2) ){

                set<int> indexes;

                int that_node_index = a;

                while(that_node_index != -1){
                    indexes.insert(that_node_index);
                    that_node_index = nodes[that_node_index].parent_index;
                }


                that_node_index = b;

                while(that_node_index != -1){
                    indexes.insert(that_node_index);
                    that_node_index = nodes[that_node_index].parent_index;
                }

                int summ = time * indexes.size();
                int flag = 1;
                for (auto index : indexes){

                    if (nodes[index].working == false){
                        flag = 0;
                    }
                    summ -= nodes[index].time;
                }

                if (flag){
                    cout << summ << endl;
                }else{
                    cout << -1 << endl;
                }
            }else{
                cout << -1 << endl;
                /// Нода не подключена к система в принципе.
            }

            /// Считать сумму
        }
    }
    return 0;
}
