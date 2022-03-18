#pragma comment(linker, "/STACK:36777216")

#include <iostream>
#include <vector>
#include <set>
#include <fstream>


//#define fin cin

using namespace std;

const int size_ = 100000; /// 100000

const int secret_number = -1337;

int Calculated[size_];
vector<int> arci[size_];

int calculate(int vertex){

    if (Calculated[vertex] != secret_number){
        return Calculated[vertex];
    }

    set<int> used;
    int n = arci[vertex].size();
    for(int i =0;i<n;i++){
        used.insert(calculate( arci[vertex][i] ));
    }
    int returner = 0;

    while(used.find(returner) != used.end()){
        returner++;
    }

    Calculated[vertex] = returner;

    return returner;

}

int main()
{
    ifstream fin("input.txt");

    int n,m;
    fin >> n >> m;
    for(int i =0;i<m;i++){
        int a,b;
        fin >> a >> b;



        arci[a-1].push_back(b-1);

    }

    cout << "konec vvoda" << endl;

    for(int i =0;i<n;i++){
        Calculated[i] = secret_number;
    }

    for(int i =0;i<n;i++){
        cout << calculate(i) << endl;
    }

    // << "Hello world!" << endl;
    return 0;
}
