#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

int64_t to_num(char c){
    if ( c >= '0' && c <= '9' ) return c - '0';
    return c - 'A' + 10;
}

bool IsSquare(int64_t number){
    return (int64_t)(sqrt( abs(number))) == sqrt( abs(number));
}

/// return all divisors
vector<int64_t> all_divisers(int64_t number){
    number = abs(number);
    vector<int64_t> ans;
    int64_t sqrt_= sqrt( number );
    for(int i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(int counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}

vector<int64_t> poly;

bool isMinus = false;
bool isMinus2 = false;
string num_runner = "";
int64_t max_val = 0;
uint64_t max_pol_size = 0;

void update(){
    bool sign = isMinus ^ isMinus2;
    max_pol_size = max(max_pol_size, num_runner.size());
    for(int j = 0; j < num_runner.size(); ++j){

        max_val = max(max_val, to_num(num_runner[j]));

        if (sign){ /// negative
            poly[num_runner.size() - j - 1] -= to_num(num_runner[j]);
        }else{
            poly[num_runner.size() - j - 1] += to_num(num_runner[j]);
        }

    }

    num_runner = "";

}

int main()
{



    string rq;
    getline(cin,rq);


    poly.resize(1000000);

    for(int i = 0; i < 1000000 + 50; ++i){
        poly[i] = 0;
    }


    for(int i = 0; i < rq.size(); ++i){


        if (rq[i] == ' '){
            update();
            continue;
        }

        if (rq[i] == '+'){
            update();
            isMinus = false;
            continue;
        }

        if (rq[i] == '-'){
            update();
            isMinus = true;
            continue;
        }

        if (rq[i] == '='){
            update();
            isMinus = false;
            isMinus2 = true;
            continue;
        }





        num_runner += rq[i];



    }

    update();

    int non_zero_index = -1;

    for(int i = 0; i < max_pol_size + 50; ++i){
        if (poly[i] != 0){
            non_zero_index = i;
            break;
        }
    }

    if (non_zero_index == -1){
        /// any answer is right
        if (max_val == 0){
            max_val = 1;
        }
        cout << max_val+1;
        return 0;
    }

    auto vc = all_divisers(abs(poly[non_zero_index]));
    //cout << endl;

    //for(auto v : vc){
    //    cout << v << " ";
    //}
    //cout << endl;

    /**
    1000000439,
    1000002173,
    1000003247,
    **/

    for(const int64_t& candidate : vc){
        if (candidate <= max_val) continue;
        bool failure = false;


        int64_t runner = 0;
        int64_t mult = 1;

        for(int i = 0; i < max_pol_size + 50; ++ i){
            runner += mult*poly[i];

            runner += 1000000439ull* (1000003111ull);
            runner %= 1000000439ull;

            mult *= candidate;
            mult %= 1000000439ull;
        }

        if (runner != 0){
            failure = true;
        }

        runner = 0;
        mult = 1;

        for(int i = 0; i < max_pol_size + 50; ++ i){
            runner += mult*poly[i];

            runner += 1000002173ull* (1000003111);
            runner %= 1000002173;

            mult *= candidate;
            mult %= 1000002173;
        }

        if (runner != 0){

            failure = true;
        }

        runner = 0;
        mult = 1;

        for(int i = 0; i < max_pol_size + 50; ++ i){
            runner += mult*poly[i];

            runner += 1000003247ull* (1000003111);
            runner %= 1000003247;

            mult *= candidate;
            mult %= 1000003247;
        }

        if (runner != 0){
            failure = true;
        }

        if ( !failure){
            cout << candidate;
            return 0;
        }
    }

    cout << "-1";

    return 0;
}
