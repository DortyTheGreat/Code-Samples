#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

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

int const SIZEE_=10000; // Размер Контейнера Чисел
/// Длинные Числа основанные на "Нестабильных" Битах
class PosSSCouSys{

public:
    int nums[SIZEE_];
    int sizeOfNum;
    int BaseChisleniya;

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

    void read_data(int SS){
    string stream_;
    cin >> stream_;
    read_data(SS,stream_);

    }

    void read_data(){
    read_data(10);
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
    void _plus(PosSSCouSys custom){
    for(int i=0;i<SIZEE_;i++){
        nums[i]=nums[i]+custom.nums[i];


    }
    Stabilize();
    }

    void _minus(PosSSCouSys custom){
    for(int i=0;i<SIZEE_;i++){
        nums[i]=nums[i]-custom.nums[i];


    }
    Stabilize();
    }

    void _mult(int mult){
    for(int i=0;i<SIZEE_;i++){
        nums[i]=nums[i]*mult;

    }
    Stabilize();
    }

    void _shift_right(){
        PosSSCouSys result;

        for(int i=SIZEE_-1;i>0;i--){

            nums[i] = nums[i-1];

        }
        nums[0] = 0;

    }

    bool operator <(PosSSCouSys& right) {
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

    bool operator <= (PosSSCouSys& right){
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
