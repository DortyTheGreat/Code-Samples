#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;
    vector<int> nach, kon;
    for(int i = 0;i< n;i++){
        int a,b;
        cin >> a >> b;
        if (b == 0){
            b = 2000000000;
        }
        nach.push_back(a);
        kon.push_back(b);
    }

    sort(nach.begin(),nach.end());
    sort(kon.begin(),kon.end());

    int cou = 0;

    int h1=0,h2=0;

    while(1){

    }

    cout << "Hello world!" << endl;
    return 0;
}
