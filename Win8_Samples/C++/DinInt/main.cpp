#include <iostream>
#include <vector>

using namespace std;

#define _OPEN_SYS_ITOA_EXT

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

long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   if(b == 0){return a;}
   while(1){

    a=a%b;
    if(a==0){break;}else{if(a<b){swap(a,b);}}

   }
  return b;

}


class Fraction{
public:
    long long Numerator=0; /// p, числитель
    long long Denominator=0; /// q, знаменатель

    void Rationalize(){

    long long NOD_ = NOD(Numerator,Denominator);
    //cout << NOD_ << endl;
    Numerator/= NOD_;
    Denominator /= NOD_;

    }

    void read(string SeparatorString){
        string Carret;
        getline(cin,Carret);
        Numerator = stoll(Carret.substr(0,Carret.find(SeparatorString)));
        Denominator = stoll(Carret.substr(Carret.find(SeparatorString)));

    }

    void print(string SeparatorString){
        cout << Numerator << SeparatorString << Denominator << endl;
    }


};

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

class BigFloat : public PosSSCouSys {
public:
    int BitsForPoint = 30;
    ///Можно читать, как ".5" или "0.5" или "1.5" или "3" или "4.0"
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

    int shift = 1;


    if(_stream.find('.') != -1){
        shift =_stream.size() - _stream.find('.');

        _stream.erase(_stream.find('.'),1);
    }

    int thisCou = _stream.size();

     sizeOfNum=_stream.size() + BitsForPoint - shift + 2;
    //cout <<  sizeOfNum << endl;
    for(int i=0;i<thisCou;i++){
         nums[(SIZEE_ - _stream.size() - BitsForPoint) + i + shift -2]=FromCharToInt(_stream[i]);
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




    string return_ans(){
        string ans="";

        if( isNegative) ans = "-";

        int flag=0;
        for(int i=0;i<SIZEE_;i++){

            if (i == SIZEE_ - BitsForPoint - 1){
                if (flag == 0){ans+= "0";}
                ans+= ".";
                flag = 1;
            }

            if( nums[i] != 0){flag=1;}



            if(flag) {ans= ans + FromIntToChar( nums[i]);}

        }
        return ans;
    }



    void ChangeFloatBase(int TO) {
        int FROM =  BaseChisleniya;
         ChangeBase(TO);
        for(int i=0;i< BitsForPoint+1;i++){
             _mult(TO);
        }

        for(int i=0;i< BitsForPoint+1;i++){
             _divide(FROM);
        }


    }

    Fraction GetFraction(){
        Fraction that;
        that.Denominator = 1;
        that.Numerator = 0;

        for(int i=SIZEE_-1;i>SIZEE_-1-BitsForPoint - 1;i--){
            that.Numerator += that.Denominator*nums[i];
            that.Denominator*= BaseChisleniya;
        }

        //that.Rationalize();

        for(int i=SIZEE_-1-BitsForPoint - 1;i>SIZEE_-1-BitsForPoint - 20;i--){
            that.Numerator += that.Denominator*nums[i];
        }
        //that.Numerator

        that.Rationalize();

        return that;
    }
};


class DinInt{
public:
    vector<long long> data_container;

    /*

    indexes -> (0, 1, 2)
    143 ==     {3, 4, 1}

    */


    int Base = 10;
    bool isNegative = false;

    void BitStabile(int bit_position){

        if (data_container[bit_position] >= Base){
            if ((data_container.size()-1) > bit_position){
                data_container[bit_position+1]++;
                data_container[bit_position]-= Base;
                BitStabile(bit_position+1);
            }else{
                data_container.push_back(1);
                data_container[bit_position]-= Base;
            }
        }


    }

    void NegBitStabile(int bit_position){

        if (data_container[bit_position] < 0){
            if ((data_container.size()-1) > bit_position){
                data_container[bit_position+1]--;
                data_container[bit_position]+= Base;
                NegBitStabile(bit_position+1);
            }else{
                /// Такого быть не должно!
                cout << "EXCEPTION COUGHT!";
                return;
            }
        }


    }

    void remove_leading_zeros(){

        int data_container_size = DinInt_.data_container.size();

        for(int i = 0;i<data_container_size;i++){
            /// HERE!
        }
    }


    void Nullify(){

        data_container.clear();
        isNegative = false;
    }

    friend istream& operator>> (std::istream &in, DinInt &DinInt_){
        // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
        // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса

        DinInt_.Nullify();

        string stream_;
        in >> stream_;

        for(int i =stream_.size()-1;i>-1;i--){
            DinInt_.data_container.push_back( FromCharToInt(stream_[i]));
        }

        return in;
    }



    friend ostream& operator<< (ostream &out, const DinInt &DinInt_){
        string stream_ = "";

        if (DinInt_.isNegative){stream_="-";}

        int data_container_size = DinInt_.data_container.size();

        for(int i =data_container_size-1;i>-1;i--){

            stream_ += FromIntToChar(DinInt_.data_container[i]);

        }

        out << stream_;

        return out;
    }



    friend DinInt operator+ ( DinInt &that, DinInt another){

        if (that.data_container.size() < another.data_container.size()){
            swap(that,another);
        }

        /// that >= another (по размеру)

        int another_size = another.data_container.size();

        for(int i =0;i< another_size;i++){

                that.data_container[i] += another.data_container[i];
                that.BitStabile(i);
        }




        return that;

    }

    friend DinInt operator- ( DinInt &that, DinInt another){

        bool NegFlag = false;


        if (that < another){
            swap(that,another);
            NegFlag ^= 1;
        }


        /// that >= another вообще

        int another_size = another.data_container.size();

        for(int i =0;i< another_size;i++){

                that.data_container[i] -= another.data_container[i];
                that.NegBitStabile(i);
        }



        that.isNegative = NegFlag;
        return that;

    }

    void operator= ( long long another){

        Nullify();

        if (another == 0){
            data_container.push_back(0);
            return;
        }

        while(another != 0){
            data_container.push_back(another%Base);
            another/= Base;
        }

    }

    bool operator <(DinInt& right) {
        if (this->isNegative) {
            if (right.isNegative) return (*this<right);
            else return true;
        }
        else if (right.isNegative) return false;
        else {

                if (data_container.size() != right.data_container.size()){
                    return (data_container.size() < right.data_container.size());
                }

                int data_container_size = data_container.size();

                for (long long i = data_container_size - 1; i > -1; --i) {
                    if (data_container[i] != right.data_container[i]) return data_container[i] < right.data_container[i];

                }

                return false;

        }
    }

    bool operator <= (DinInt& right){
        return !( right < *this);
    }

};



int main()
{
    DinInt Num,Num2;



    cin >> Num >> Num2;

    cout << Num - Num2;

    return 0;
}
