#include <iostream>


#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

#define int long long

int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}


using namespace std;


signed main()
{




    for(int test = 1; test <= 100; test++){
        ofstream fout("out" + to_str(test) + ".txt");

        int t = rnd(1,pow(1.07,test));
        fout << t << endl;
        for(int i = 0;i < t;++i){

            int type = rnd(1,2);

            if (type == 1){
                int p,q,h;

                p = rnd(1,999 * 999 * 999);
                q = rnd(p+1,999*999 *999 + 3);
                h = rnd(0,999 * 999 * 999);

                fout << p << " " << q << " " << h << endl;
            }else{
                int p,q,h;

                p = rnd(1,999 * 999 * 999);
                q = rnd(p+1,p+500);
                h = rnd(0,999 * 999 * 999);

                fout << p << " " << q << " " << h << endl;
            }


        }


    }





    return 0;
}
