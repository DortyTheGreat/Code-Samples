#include <iostream>

using namespace std;

#define int long long

const int size_ = 1000002;

int Calculated[size_];

string fillSpaces(string str, int spaces){
    while(str.size() != (spaces)){
            str += "0";
        }
        return str;
}

bool StringCompare(string T1, string T2){
    if (T1.size() != T2.size()){
        return T1.size() < T2.size();
    }

    return T1 < T2;
}



long long D[1000][10];
long long modulo = 1e9;

long long stabile(long long num){
    num = num%modulo;

    if (num <0){
        return modulo + num;
    }

    return num;
}

long long calculate(string val){
    if (val.size() == 1){
        return (val[0] - '0');
    }
if (val.size() == 0 ){
    return 1;
}

long long cou_all_smaller =0;
for(int i =0;i<10;i++){
cou_all_smaller += D[val.size() - 2][i];
cou_all_smaller = stabile(cou_all_smaller);
}

int Numbers[10];int h =0;
for(int i=1;i<10;i++){
    if ((val[0]-'0') >= i){
        ///

        Numbers[h] = i;h++;
    }
}

for(int i =0;i<h-1;i++){
   /// cout << "BIBA: " << Numbers[i] << endl;
    cou_all_smaller += D[val.size() - 1][9 - Numbers[i]];
    cou_all_smaller = stabile(cou_all_smaller);
   /// cout << "PASSIV: " << D[val.size() - 1][9 - Numbers[i]] << endl;
}

///cout << "BEBRA: " << val.substr(1) << endl;
///cout << "BEFORE_BEBRA: " << cou_all_smaller <<endl;
if (val[0] <= val[1]){
cou_all_smaller += calculate(val.substr(1));
cou_all_smaller = stabile(cou_all_smaller);

long long BEBRINKA = (calculate(val[0] + fillSpaces("",val.size() - 2)));
if (val.size() == 2){
    BEBRINKA-= 1;
}
cou_all_smaller -= BEBRINKA;
cou_all_smaller = stabile(cou_all_smaller);
///cout << "BEBRINKA: " << BEBRINKA << endl;
}



cou_all_smaller = stabile(cou_all_smaller);

///cout << "AFTER_BEBRA: " << cou_all_smaller <<endl;

return stabile(cou_all_smaller - 1);




}


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



    void _divide(int right){

        if (right == 0) return;
        //PosSSCouSys b = right;
        //b._is_negative = false;
        PosSSCouSys result, current;
        result.BaseChisleniya = BaseChisleniya;
        current.BaseChisleniya = BaseChisleniya;

        for (int i=SIZEE_-1;i>-1;i--) {
            current._shift_right();
            current.nums[0] = nums[i];
            //current._remove_leading_zeros();
            int x = 0, l = 0, r = BaseChisleniya;
            while (l <= r) {
                int m = (l + r) / 2;
                PosSSCouSys t;
                long long NUMME = right * m;
                t.read_data(10,to_string(NUMME));
                if (t <= current) {
                    x = m;
                    l = m + 1;
                }
                else r = m - 1;
            }

            result.nums[i] = x;

            PosSSCouSys t2;
            long long NUMME2 = right * x;
            t2.read_data(10,to_string(NUMME2));
            current._minus(t2);
        }

        result.isNegative = ((isNegative) != (right > 0));
        *this = result;

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


signed main()
{




    modulo = modulo + 7;



    for(int i =0;i<1000;i++){
        for(int j =0;j<10;j++){
            D[i][j] = 0;
        }
    }

    string b;


    PosSSCouSys a,c;

    a.read_data();
    cin >> b;
    c.SetToOne();
    c.BaseChisleniya = 10;
    a._minus(c);

    string AA = a.return_ans();

    if (AA == ""){
        AA = "0";
    }

    for(int j = 0;j<10;j++){
        D[0][j] = 1;
    }

    for(int i =1;i<1000;i++){
        for(int j = 0;j<10;j++){

            for(int cou = 0;cou <= j;cou++){
            D[i][j] += D[i-1][cou];
            D[i][j] = stabile(D[i][j]);
            }
            D[i][j] = stabile(D[i][j]);

            ///cout <<i <<" : " << j << " : " << D[i][j] << endl;


        }
    }


    ///cout << AA << endl;
    cout << calculate(b) - calculate(AA);







}
