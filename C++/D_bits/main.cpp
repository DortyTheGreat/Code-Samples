#include <iostream>
#include "DortyLibs/DortyBuild.h"
#include "DortyLibs/DortyGraph.h"
void YesNo(bool num){
    if (num){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}
#include <iomanip>
#include <algorithm>
using namespace std;
bool ravn(Graph G1, Graph G2){
    if (G1.Size != G2.Size){
        return 0;
    }
    for (int i =0;i<G1.Size;i++){
        if ( !(G1.Nodes[i] == G2.Nodes[i])){
            return 0;
        }
    }

    return 1;
}


int main()
{
    AppBuild();


    Graph G1,G2;
    G1.ReadAsSquareMatrix();
    G2 = G1;
    G1.ReverseGraph();
    YesNo(G1 == G2);


    return 0;
}
