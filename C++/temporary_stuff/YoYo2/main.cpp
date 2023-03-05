#include <iostream>

using namespace std;
#define int long long


/// 99 100 789


/**
789 - 700 = 89.
ceil(89 / decr) = ceil(89 / 8) = 12

789 - 12*8 = 693. added = {(693 + 8) + (693 + 16) + ... + 789}

== 693 * 12 + 8*(12+1)*12/2


*/
/// 789 -> 781
/// 800 -> 792
/// 801 -> 792

/// decrement = floor((number-1)/div)+1.

/**

701-800 decr=8
801-900 decr=9

*/



/**

98/100

100 -> 98 {2}
101 -> 98 {3}
102 -> 99 {3}


150 -> 147 {3}
151 -> 147 {4}

So... how to find decr base on p,q,h ?


97/100



100 -> 97 {3}
101 -> 97 {4}

133 -> 129 {4}
134 -> 129 {5}

166 -> 161 {5}
167 -> 161 {6}


200 -> 194 {6}
201 -> 194 {7}

20000 -> 19400 {600}




floor ( (h-2)/(q-p) ) + 1


decr = h - (h*p/q)



а теперь пытаемся понять, когда впервые decr поменяется.


Нпример

h = 121

97 / 100

decr = 4

На сотне decr = 3.

Но как понять, что это на сотне?

121 - 100 = 21. ceil(21 / decr) = 6


Но как найти эту сотню?

g(121) -> 100


На самом деле нужно разложить число на одну из видов форм

33 = floor( 100/(q-p) )

100*k1 + 33*k2

где k1 - любое, k2 =

k1 = 121 / 100 = 1

k2 = ceil(121 % 100 / 33 ) = 1


=> new
k1 = 1
k2 = 0


*/

int simple(int p,int q,int h){

    int summ = 0;

    while(h){
        summ += h;
        h = h*p/q;
    }
    return summ;
}

signed main()
{
    int p,q,h;
    cin >> p >> q >> h;
    int summ = 0;
    double r = double(p)/q;
    if (r < 0.9){
        cout << simple(p,q,h);
    }else{
        while (h){
            int decr =  h - (h*p/q);

            cout << "h= " << h << endl;
            cout << "decr: " << decr << endl;

            int k2 = (h % q);

            int extra;

            int w_33 = q/(q-p);

            cout << "w_33: " << w_33 << endl;

            if (k2 == 0){
                cout << "SHIT" << endl;
                extra = q * (h/q - 1) + ( w_33 * ( (q-p - 1 ) ));
            }else{
                extra = q * (h/q) + ( w_33 * ( (k2-1)/( w_33 ) ));
            }

            cout << "limit: " << extra << endl;

            extra = h - extra;

            cout << "extra: " << extra << endl;

            int times_ = (extra-1)/ decr + 1;
            //cout << "t: " << times_ << endl;

            h -= times_ * decr;
            summ += h*times_ + decr*(times_)*(times_+1)/2;


        }
        //cout << h << endl;
        cout << summ;
    }


    return 0;
}
