#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

char FromIntToChar(int a){
    if (a >= 0 && a <= 10){
        return (a + '0');
    }
    return (a - 10) + 'A';
}

int FromCharToInt(char a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }
    return (a - 'A')+10;
}

const size_t SIZEE_=10000; // Размер Контейнера Чисел
/// Длинные Числа основанные на "Нестабильных" Битах
class BigInt{

public:
    int nums[SIZEE_];
    int sizeOfNum;
    int BaseChisleniya = 10;

    bool isNegative = false;

    void read_data(int SS, string __stream){
        for(int i=0;i<SIZEE_;i++){
            nums[i]=0;
        }

        BaseChisleniya=SS;
        string _stream = __stream;

        if(_stream[0] == '-'){
            isNegative = true;
            _stream.erase(_stream.begin());
        }

        sizeOfNum=_stream.size();
        for(int i=0;i<sizeOfNum;i++){
            nums[(SIZEE_ - sizeOfNum) + i]=FromCharToInt(_stream[i]);
        }

    }

    void read_data(int SS=10){
        string stream_;
        cin >> stream_;
        read_data(SS,stream_);

    }



    void SetToZero(){
        for(int i=0;i<SIZEE_;i++){
            nums[i]=0;
        }
    }

    void SetToOne(){
        SetToZero();
        nums[SIZEE_-1]=1;
    }



    void OneNumTransform(int pos){

        nums[pos-1]=nums[pos-1] + nums[pos]/BaseChisleniya;
        nums[pos]= nums[pos]%BaseChisleniya;

        if( nums[pos] < 0 ){nums[pos]+=BaseChisleniya;nums[pos-1]--;}
    }


    void Stabilize(){
        for(int i=SIZEE_-1;i>-1;i--){
            OneNumTransform(i);
        }
    }


    void debugOutPut(){
        for(int i=0;i<SIZEE_;i++){
            cout << nums[i] << " ";
        }
        cout << endl;
    }

    /// Попарно прибавляет контейнеры чисел, Затем стабилизирует. ВНИМАНИЕ! НЕ СКЛАДЫВАЕТ КОРРЕКТНО ЧИСЛА РАЗНЫХ БАЗИСОВ!

    BigInt& operator+= (const BigInt& other){

        for(int i=0;i<SIZEE_;i++){
            nums[i] += custom.nums[i];
        }
        Stabilize();
        return *this;
    }


    BigInt& operator-= (const BigInt& other){

        for(int i=0;i<SIZEE_;i++){
            nums[i] -= custom.nums[i];
        }
        Stabilize();
        return *this;
    }

    BigInt& operator*= (int mult){

        for(int i=0;i<SIZEE_;i++){
            nums[i] *= mult;
        }
        Stabilize();
        return *this;
    }

    void _shift_right(){
        PosSSCouSys result;

        for(int i=SIZEE_-1;i>0;i--){
            nums[i] = nums[i-1];

        }
        nums[0] = 0;
    }

    bool operator< (const BigInt& right) const{
        if (this->isNegative) {
            if (right.isNegative) return (*this<right);
            else return true;
        }
        else if (right.isNegative) return false;
        else {

                for (long long i = SIZEE_ - 1; i > -1; --i) {
                    if (nums[i] != right.nums[i]) return nums[i] < right.nums[i];
                }

                return false;

        }
    }

    bool operator <= (BigInt& right){
    return !( right < *this);
    }


    ///Делит число на divider, возвращает остаток
    int _divide(int divider){
        int ostatok = 0;
        for(int i=0;i<SIZEE_ - 1;i++){
            nums[i+1] += nums[i]%divider * BaseChisleniya;
            nums[i] -= nums[i]%divider;

        }
        ostatok = nums[SIZEE_ - 1] % divider;
        for(int i=0;i<SIZEE_;i++){

            nums[i] /= divider;
        }
        Stabilize();
        return ostatok;
    }

    string return_ans(){
        string ans="";

        if(isNegative) ans = "-";

        int flag=0;
        for(int i=0;i<SIZEE_;i++){
                if(nums[i] != 0){flag=1;}
        if(flag) {ans= ans + FromIntToChar(nums[i]);}

        }
        return ans;
    }

    PosSSCouSys operator+ (const PosSSCouSys& c) const
    {
      PosSSCouSys result;
      result = *this;
      result._plus(c);
      return result;
    }

    void ChangeBase(int TO) {

        PosSSCouSys num2,mask,ans;

        mask.SetToOne();
        ans.SetToZero();

        mask.BaseChisleniya = TO;
        ans.BaseChisleniya = TO;
        ans.isNegative = isNegative;
        //num.debugOutPut();


        for(int i=0;i<sizeOfNum;i++){

        //mask.debugOutPut();

        num2 = mask;
        num2._mult(nums[SIZEE_- i -1]);

        //num2.debugOutPut();

        ans._plus(num2);
        //ans.Stabilize();

        //ans.debugOutPut();

        mask._mult(BaseChisleniya);
        //mask.Stabilize();
        }
        //num.transformato(2);
        //ans.debugOutPut();


        *this = ans;
    }
};

class BigFloat {
public:
    int BitsForPoint = 50;
    PosSSCouSys BigInt;
    void read_data(int SS, string __stream){
        for(int i=0;i<SIZEE_;i++){
            BigInt.nums[i]=0;
        }

    BigInt.BaseChisleniya=SS;
    string _stream = __stream;

    if(_stream[0] == '-'){
        BigInt.isNegative = true;
        _stream.erase(_stream.begin());
    }

    int shift = 1;


    if(_stream.find('.') != -1){
        shift =_stream.size() - _stream.find('.');
        /// обработка дробной части
        _stream.erase(_stream.find('.'),1);
    }

    int thisCou = _stream.size();

    BigInt.sizeOfNum=_stream.size() + BitsForPoint - shift + 2;
    //cout << BigInt.sizeOfNum << endl;
    for(int i=0;i<thisCou;i++){
        BigInt.nums[(SIZEE_ - _stream.size() - BitsForPoint) + i + shift -2]=FromCharToInt(_stream[i]);
    }

    }



    string return_ans(){
        string ans="";

        if(BigInt.isNegative) ans = "-";

        int flag=0;
        for(int i=0;i<SIZEE_;i++){

            if (i == SIZEE_ - BitsForPoint - 1){
                if (flag == 0){ans+= "0";}
                ans+= ".";
                flag = 1;
            }

            if(BigInt.nums[i] != 0){flag=1;}



            if(flag) {ans= ans + FromIntToChar(BigInt.nums[i]);}

        }
        return ans;
    }



    void ChangeFloatBase(int TO) {
        int FROM = BigInt.BaseChisleniya;
        BigInt.ChangeBase(TO);
        for(int i=0;i< BitsForPoint+1;i++){
            BigInt._mult(TO);
        }

        for(int i=0;i< BitsForPoint+1;i++){
            BigInt._divide(FROM);
        }


    }
};


signed main() {
    int FROM;
    int TO;
    cout << "FROM: "; cin >> FROM;
    cout << "TO: "; cin >> TO;
    string str;
    cin >> str;
    BigFloat BF;
    BF.read_data(FROM,str);
    //BF.BigInt.debugOutPut();
    //cout << BF.return_ans() << endl;

    BF.ChangeFloatBase(TO);

    //BF.BigInt.debugOutPut();

    cout << BF.return_ans();


    //PosSSCouSys buba;

    //buba.read_data(10);

    //buba.ChangeBase(2);
    //cout << buba.return_ans();

/*
    ifstream INP("input.txt");
    ofstream OUT("output.txt");

    PosSSCouSys num,num2;

    string abg;
    INP >> abg;

    num.read_data(10,abg);
    int a;
    INP >> a;
    int ost;
    ost = num._divide(a);
    //num.Minus_Remove_Trables();
    //num.debugOutPut();

    //num.debugOutPut();

    OUT << num.return_ans() << endl << ost;

*/
}

using namespace std;





signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    BigUnsigned a,b;
    while(cin >> a >> b){
        cout << a + b << endl;
    }




}


