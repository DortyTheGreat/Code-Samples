#include <iostream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

struct employ{
    int parent = -1;
    int dist_to_A = -1;
    int dist_to_B = -1;
    int isA;
};

vector<employ> vc;

int getA(int index){
    if (vc[vc[index].parent].isA || vc[vc[index].parent].parent == -1) return vc[index].dist_to_A = 0;
    if (vc[index].dist_to_A != -1) return vc[index].dist_to_A;
    return vc[index].dist_to_A = 1 + getA(vc[index].parent);
}

int getB(int index){
    if (!vc[vc[index].parent].isA || vc[vc[index].parent].parent == -1) return vc[index].dist_to_B = 0;
    if (vc[index].dist_to_B != -1) return vc[index].dist_to_B;
    return vc[index].dist_to_B = 1 + getB(vc[index].parent);
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    n += 1;
    vc.resize(n);

    for(int i =1; i < n; ++ i){
        char c;
        cin >> c;
        vc[i].isA = (c == 'A');
    }

    int zero;
    cin >> zero;

    stack<int> nums;

    bool arr[1001 * 1001];

    for(int i = 0; i < 1001 * 1001; ++i){
        arr[i] = 0;
    }

    arr[0] = 1;
    nums.push(0);

    for(int i = 0; i < (n-1)*2; ++i){
        int num;
        cin >> num;
        if (arr[num] == 0){
            arr[num] = 1;
            vc[num].parent = nums.top();
            nums.push(num);
        }else{
            nums.pop();
            arr[num] = 0;
        }
    }
    cin >> zero;

    for(int i = 1; i < n; ++i){
        if (vc[i].isA)
            cout << getA(i) << " ";
        else
            cout << getB(i) << " ";
    }

    cout << endl;
    for(int i = 0; i < n; ++i){
        ///cout << vc[i].parent << " ";
    }

    return 0;
}
