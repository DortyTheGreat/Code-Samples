#pragma GCC optimize("O3")
#pragma target("avx2.0")

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <queue>


#include "Graph.h"

using namespace std;

#define int long long


signed main() {
  int n, m;
  cin >> n;
  Graph G1;
  G1.init(n);
   /// хз, просто массив

  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    G1.InsertNewArc(u-1,1,v-1);
  }

  Graph G2 = G1.Get_Condensated_Graph();


    int counter_ = 0;
    cout << endl;
  for(int i = 0;i< G2.Size;i++){

    for(Arc that : G2.Arcs[i]){
        counter_++;
        cout << i<<" " <<that.direction << endl;
    }

  }
  cout << endl;

  cout << counter_ << endl;
  cout << G2.Size;

  return 0;
}
