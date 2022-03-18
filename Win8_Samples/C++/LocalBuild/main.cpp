
#include <iostream>
#include <algorithm>

#include "DortyGraph.h"
#include "DortyBuild.h"
using namespace std;




int main() {
    AppBuild();

    Graph G1;
    G1.ReadAsSquareMatrix();



    //G1.DisorientGraph();

    int K;
    cin >> K;

    if (G1.Size == 1){
        cout << endl;
        return 0;
    }

    for(int from = 0;from < G1.Size;from++){
        for(int to = from+1;to<G1.Size;to++){


                G1.Dijkstra_Search(from);



                int NodeStartIndex = to;

                int ANSES[1000];int h=0;
                int isEnd = 1;
                int flag = 1;

                int ANSUA = 0;

                while(isEnd){
                    flag = 1;
                    Node thatNode = G1.Nodes[NodeStartIndex];
                    for(Arc that : G1.Arcs[NodeStartIndex]){
                        if (G1.Nodes[that.direction].SearchedDistance == thatNode.SearchedDistance-that.value){
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
                                ANSES[h] = from;
                                h++;
                                break;
                        }

                    if (flag){
                            ANSES[0] = -1;h = 1; break;

                    }
                }


                if (G1.Nodes[to].SearchedDistance == G1.pseudo_inf){
                    //cout << "("<<from+1<<","<<to+1<<"): 0" << endl;
                }else{
                    if (G1.Nodes[to].SearchedDistance == K){
                  cout << from+1 << " " << to+1 << endl;
                    }
                }


          ///END <-
        }
    }
                return 0;
    //for(int i =0;i<n;i++){
    //    cout << G1.Nodes[i].value;
    //}

}
