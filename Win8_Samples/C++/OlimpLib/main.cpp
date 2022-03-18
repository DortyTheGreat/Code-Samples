#include <iostream>
#include "DortyBuild.h"
#include "DortyGraph.h"
using namespace std;

int main()
{
    AppBuild();

    Graph G1;

    long long n,m;
    cin >> n >> m;

    G1.init(n);

    long long from,to;
    cin >> from >> to;

    to--;
    from--;

    for(long long i =0;i<m;i++){
        long long a,b,c;
        cin >> a >> b >> c;
        a--;
        b--;
        G1.InsertNewArc(a,c,b);
        G1.InsertNewArc(b,c,a);
    }



    G1.Dijkstra_Search(from);

    //G1.DisorientGraph();


    long long ANSES[1000];long long h=0;
    long long isEnd = 1;
    long long flag = 1;

    long long ANSUA = 0;

    long long NodeStartIndex = to;

    while(isEnd){
        flag = 1;
        Node thatNode = G1.Nodes[NodeStartIndex];
        for(Arc that : G1.Arcs[NodeStartIndex]){
            ///G1.Nodes[that.direction].used == thatNode.used-1
            if ((G1.Nodes[that.direction].SearchedDistance == thatNode.SearchedDistance-that.value) && (G1.Nodes[that.direction].used == thatNode.used-1)){
                if (G1.Nodes[that.direction].SearchedDistance != G1.pseudo_inf){
                    //cout << NodeStartIndex << endl;
                    ANSES[h] = NodeStartIndex;h++;


                    NodeStartIndex = that.direction;
                    flag = 0;
                    break;
                }
            }
        }

        if (NodeStartIndex == from){
                    isEnd = 0;
                    break;
            }

        if (flag){
                ///cout << "0"; return 0;
                break;
        }
    }

    ANSES[h] = from;
    h++;

    cout << G1.Nodes[to].SearchedDistance << endl << G1.Nodes[to].used-2 << endl;
    for(long long i = h-2;i>0;i--){
        cout << ANSES[i]+1 << " ";
    }

    ///cout << "Hello world!" << endl;
    return 0;
}
