#include <iostream>

using namespace std;

struct B{ public: int A; };
struct C{ public: B B_; };
struct D{ public: C C_; };
struct E{ public: D D_; };
struct F{ public: E E_; };
struct G{ public: F F_; };
struct H{ public: G G_; };
struct I{ public: H H_; };
struct J{ public: I I_; };
struct K{ public: J J_; };
struct L{ public: K K_; };
struct M{ public: L L_; };
struct N{ public: M M_; };


int main()
{
    N aboba;
    aboba.M_.L_.K_.J_.I_.H_.G_.F_.E_.D_.C_.B_.A = 0;

    for(int i = 0;i<300 * 1000 * 1000; ++i){
        aboba.M_.L_.K_.J_.I_.H_.G_.F_.E_.D_.C_.B_.A++;
        aboba.M_.L_.K_.J_.I_.H_.G_.F_.E_.D_.C_.B_.A++;
        aboba.M_.L_.K_.J_.I_.H_.G_.F_.E_.D_.C_.B_.A++;
        aboba.M_.L_.K_.J_.I_.H_.G_.F_.E_.D_.C_.B_.A++;
        aboba.M_.L_.K_.J_.I_.H_.G_.F_.E_.D_.C_.B_.A++;


    }

    /**
    class - 2.1 s
    struct - 2.1 s
    */

    cout << "Hello world!" << endl;
    return 0;
}
