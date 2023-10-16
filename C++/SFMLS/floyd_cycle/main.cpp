#include <iostream>

using namespace std;

void func(int& change, int len, int point_to_cycle){
    ++change;
    if (change == len+1)
        change = point_to_cycle;
}

int simple(int length, int point_to_cycle){
    int ans = 0;
    int hare = 1;
    int tort = 1;



    while (1){
        func(hare,length,point_to_cycle);
        ++ans;
        if (hare == tort) break;

        func(hare,length,point_to_cycle);
        ++ans;
        if (hare == tort) break;

        ++ans;
        func(tort,length,point_to_cycle);
        if (hare == tort) break;

    }

    return ans;
}


int smarter(int n, int c){


    int d = n - c + 1;

    /// Черепаха должна дойти до c
    int hare_then = c + ((c-1)*2 + 1 - c) % d;



    int doskakat = (c - hare_then) % d;
    if (doskakat < 0) doskakat += d;


    return (c-1)*3 + min(2,doskakat) + max(doskakat-2,0)*3;

}

int main()
{
    int n,c;
    cin >> n >> c;
    cout << smarter(n,c);
    return 0;
}
