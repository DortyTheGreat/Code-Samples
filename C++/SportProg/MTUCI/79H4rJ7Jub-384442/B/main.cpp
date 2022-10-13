/// https://codeforces.com/group/79H4rJ7Jub/contest/384442/problem/A
/// http://codeforces.com/contestInvitation/e1180f0bb5d1bfed72d2801e3764ae9614abb71e

#include <iostream>


#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    int q;
    cin >> n >> m;
    cin >> q;
    set< pair<int,int> > syner;

    for(int i = 0;i<q;++i){
        int a,b;
        cin >> a >> b;
        syner.insert({a,b});
    }



    int ans = 100000;
    for(int global_flag = 0; global_flag < 2; ++global_flag){

        int a=1,b=1; bool flag = 0;
        int steps = 0;
        int incr_ = 0;
        if (global_flag){
            if (syner.find({a,b}) != syner.end()) incr_ = 1;
            a+= b+incr_;
            steps++;
        }else{
            if (syner.find({a,b}) != syner.end()) incr_ = 1;
            b+= a+incr_;
            steps++;
        }

        while ( a < n || b < m){
            ///cout << a << " " << b << endl;
            int incr = 0;
            if (a == n){
                if (syner.find({a,b}) != syner.end()) incr = 1;
                b += a + incr;
                b = min(b,m);
                steps++;
                continue;
            }

            if (b == m){
                if (syner.find({a,b}) != syner.end()) incr = 1;
                a += b + 1;
                a = min(a,n);
                steps++;
                continue;
            }

            ///cout << a << " " << b << endl;

            if ( !(flag ^ global_flag) ){
                if (syner.find({a,b}) != syner.end()) incr = 1;
                if ( a+b+incr >= b ){
                    b = m;
                    steps++;
                    continue;
                }

            }else{
                if (syner.find({a,b}) != syner.end()) incr = 1;
                if ( a+b+incr >= a ){
                    a = n;
                    steps++;
                    continue;
                }
            }


            if ( !(flag ^ global_flag) ){
                flag ^= 1;
                if (syner.find({a,b}) != syner.end()) incr = 1;
                a += b + 1;
                a = min(a,n);
                steps++;
                continue;
            }else{
                flag ^= 1;
                if (syner.find({a,b}) != syner.end()) incr = 1;
                b += a + incr;
                b = min(b,m);
                steps++;
                continue;
            }

        }

        ans = min(ans,steps);

    }

    cout << ans << endl;

    return 0;
}
