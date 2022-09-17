/// https://codeforces.com/gym/374545/problem/I

#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for(int i = 0;i<t;++i){
        int a,b,c, a1,b1,c1, last;
        cin >> a >> b >> c >> a1>> b1 >> c1 >> last;
        cout << a<< " "<< b << " "<< last-b-a << endl;
    }
    return 0;
}
