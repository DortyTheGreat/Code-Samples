#include <iostream>
#include "WCDCgame.h"
#include <vector>
using namespace std;

const int PrettyBigNum=10000;

class Graph{
public:
    vector<int> Data[PrettyBigNum]; /// G
    int color[PrettyBigNum];
    int countStartNum=0;

    void ReadAsMatrixNM(int n, int m){
    for(int i=countStartNum;i<n+countStartNum;i++){
        for(int j=countStartNum;j<m+countStartNum;j++){
            int rec;
            cin >> rec;
            if(rec == 1){
                G[j].push_back(i);
            }

        }
}
    }

    void dfs (int v,int arg,int cou) { /// call dfs as dfs(1,-1,-100);
        /// color представляет расстояние от изначальной точки до текущей ()
        for(int i =0;i<PrettyBigNum;i++){
            color[i] = 0;
        }

    if(cou > 2 && arg == v){
        flag=1;
    }
	if(color[v]){
        return;
	}
	//parent[v] = p;
	color[v] = 1;

	//if(v == b){return;}


	for (int i=0; i<G[v].size(); ++i)
		dfs(G[v][i],arg,cou+1 );

	color[v] = 2;
}

};

int main()
{
    Box a;
    cout << "Hello world!" << endl;
    return 0;
}
