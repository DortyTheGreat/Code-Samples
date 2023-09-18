#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> symbols(n);
    vector<int> ryads(n);

    map<int,int> from_symbol_to_ryad;

    for(int i = 0; i < n; ++i){
        cin >> symbols[i];
    }

    for(int i = 0; i < n; ++i){
        cin >> ryads[i];
    }

    for(int i = 0; i < n; ++i){
        from_symbol_to_ryad[symbols[i]] = ryads[i];
    }

    int m;
    cin >> m;

    int car;
    cin >> car;

    int ans = 0;

    for(int i = 1; i < m; ++i){
        int nw;
        cin >> nw;
        if (from_symbol_to_ryad[nw] != from_symbol_to_ryad[car]) ans++;

        car = nw;
    }

    cout << ans << endl;
    return 0;
}
