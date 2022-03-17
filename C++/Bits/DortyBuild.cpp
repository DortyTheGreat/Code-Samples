/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

#include "DortyLibs/BITS.h"
#include <algorithm>
#include "DortyLibs/DortyBigInt.h"
int main()
{
    /// каммент
    AppBuild();

    ///print(reverse(input()));


    BigInt a,b;

    cin >> a;

    cout << a << endl;

    //fout.setf(ios_base::fixed);
    //fout.precision(8);

    //Polygon a;
    //fin >> a;
    //fout << Cake_algo(a);


}

*/
#include <iostream>
using namespace std;

#include <vector>


template <typename T>
ostream& operator<<(ostream &in, const vector<T> &vect) {
    int n = vect.size();



    for(int i =0;i<n;i++){

        in << vect[i] << " " ;

    }

    return in;
}

template <typename T>
istream& operator>>(istream& in, vector<T> &vect) {
    int size_;
    in >> size_;

    vect.resize(size_);

    for(int i = 0;i<size_;i++){
        in >> vect[i];
    }

    return in;
}

template <typename T>
void operator += (vector<T> &vect,T number) {
    vect.push_back(number);
}

template <typename T>
vector<T> get_all_sub_strings(T &vect){

    vector<T> ret;

    int sz = vect.size();

    for(int l = 0;l<sz;l++){
        for(int r = l+1;r<sz+1;r++){
            T obj;
            for(int cou = l;cou < r;cou ++){
                obj += vect[cou];
            }
            ret.push_back(obj);

        }
    }

    return ret;
}

template <typename T>
T sum(vector<T> &vect){
    T ret = 0;
    int sz = vect.size();
    for(int l = 0;l<sz;l++){
        ret += vect[l];
    }
    return ret;
}

template <typename T>
T min(vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = min(ret,vect[i]);
    }
    return ret;
}

template <typename T>
T max(vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = max(ret,vect[i]);
    }
    return ret;
}

template <typename T>
vector<T> list(basic_string<T> str){
    vector<T> ret;
    ret.resize(str.size());
    for(size_t i = 0;i<str.size();i++){
        ret[i] = str[i];
    }
    return ret;
}

template <typename T>
inline T first(vector<T> &vect){
    return vect[0];
}

template <typename T>
inline T last(vector<T> &vect){
    return vect[vect.size() - 1];
}


#include <vector>

void YesNo(bool arg){
    if (arg){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}

string input(){
    string returner;
    cin >> returner;
    return returner;
}

template <typename T>
T input(T ab){
    T returner;
    cin >> returner;
    return returner;
}

long long to_int(string str){
    long long mask = 1;
    size_t start_index = 0;
    long long returner = 0;
    if (str[0] == '-'){
        mask = -1;
        start_index = 1;
    }

    for(size_t i =start_index;i<str.size();i++){
        returner *= 10;
        returner += (str[i] - '0');
    }
    return returner * mask;
}

long long intput(){
    return to_int(input());
}

template <typename T, typename F>
void print(T a, F b){
    cout << a << " " << b << endl;
}

template <typename T>
T max(const vector<T> &vect){
    if (vect.size() < 1){
        return -1;
    }
    T max_ = vect[0];
    for (auto i : vect){
        max_ = max(max_,i);
    }
    return max_;
}

template <typename T>
T indexOf(const vector<T> &vect, T element){
    size_t size_ = vect.size();
    for (int i =0;i<size_;++i){
        if (vect[i] == element){
            return i;
        }
    }
    return -1;
}

template <typename T>
vector<T> slice(const vector<T> &vect, size_t elements){

    vector<T> returner;

    size_t size_ = min(vect.size(),elements);

    for (int i =0;i<size_;++i){
        returner.push_back(vect[i]);
    }
    return returner;
}

void print(string data){
    cout << data << endl;
}



#include <sstream>
template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }


  template <typename T>
  basic_string<T> reverse( basic_string<T> str){
    basic_string<T> ret = "";
    size_t sz = str.size();
    for(size_t i = 0;i < sz;i++){
        ret += str[sz - i -1];
    }
    return ret;
  }


#include <algorithm>

char FromIntToChar(int a){
switch(a){
case 0: return '0';
case 1: return '1';
case 2: return '2';
case 3: return '3';
case 4: return '4';
case 5: return '5';
case 6: return '6';
case 7: return '7';
case 8: return '8';
case 9: return '9';
case 10: return 'A';
case 11: return 'B';
case 12: return 'C';
case 13: return 'D';
case 14: return 'E';
case 15: return 'F';
case 16: return 'G';
case 17: return 'H';
case 18: return 'I';
case 19: return 'J';
case 20: return 'K';
case 21: return 'L';
case 22: return 'M';
case 23: return 'N';
case 24: return 'O';
case 25: return 'P';
case 26: return 'Q';
case 27: return 'R';
case 28: return 'S';
case 29: return 'T';
case 30: return 'U';
case 31: return 'V';
case 32: return 'W';
case 33: return 'X';
case 34: return 'Y';
case 35: return 'Z';
}
}

int FromCharToInt(char a){
if(a == '0'){return 0;}
if(a == '1'){return 1;}
if(a == '2'){return 2;}
if(a == '3'){return 3;}
if(a == '4'){return 4;}
if(a == '5'){return 5;}
if(a == '6'){return 6;}
if(a == '7'){return 7;}
if(a == '8'){return 8;}
if(a == '9'){return 9;}
if(a == 'A'){return 10;}
if(a == 'B'){return 11;}
if(a == 'C'){return 12;}
if(a == 'D'){return 13;}
if(a == 'E'){return 14;}
if(a == 'F'){return 15;}
if(a == 'G'){return 16;}
if(a == 'H'){return 17;}
if(a == 'I'){return 18;}
if(a == 'J'){return 19;}
if(a == 'K'){return 20;}
if(a == 'L'){return 21;}
if(a == 'M'){return 22;}
if(a == 'N'){return 23;}
if(a == 'O'){return 24;}
if(a == 'P'){return 25;}
if(a == 'Q'){return 26;}
if(a == 'R'){return 27;}
if(a == 'S'){return 28;}
if(a == 'T'){return 29;}
if(a == 'U'){return 30;}
if(a == 'V'){return 31;}
if(a == 'W'){return 32;}
if(a == 'X'){return 33;}
if(a == 'Y'){return 34;}
if(a == 'Z'){return 35;}

}


/// Реализация класса больших чисел, через массив нестабильных битов.
class BigInt{
private:
    void _remove_leading_zeros();
    bool _is_negative = false;

public:
    vector<int> data;
    int Base = 10;

    istream& input(int  Base_,istream& in){
        Base = Base_;
        string stream_;
        in >> stream_;

        int sz = stream_.size();

        data.resize(sz);

        for(int i = 0;i<sz;i++){
            data[i] = FromCharToInt(stream_[i]);
        }

        _remove_leading_zeros();

        return in;


    }

    friend istream& operator>>(istream& in, BigInt &bi) {
        return bi.input(10,in);

    }

    friend ostream& operator<<(ostream &in, const BigInt &bi) {

        int sz = bi.data.size();

        for(int i = 0;i<sz;i++){
            in << FromIntToChar(bi.data[i]);
        }

        return in;
    }

    /*
    void Stabilize(){
        for(int i=SIZEE_-1;i>-1;i--){
            OneNumTransform(i);
        }
    }
    */

public:

};





void BigInt::_remove_leading_zeros() {
	while (this->data.size() > 1 && this->data.front() == 0) {
		this->data.erase(data.begin());
	}

	if (this->data.size() == 1 && this->data[0] == 0) this->_is_negative = false;
}

int main()
{
    /// каммент
     

    ///print(reverse(input()));


    BigInt a,b;

    cin >> a;

    cout << a << endl;

    //fout.setf(ios_base::fixed);
    //fout.precision(8);

    //Polygon a;
    //fin >> a;
    //fout << Cake_algo(a);


}

