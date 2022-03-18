#include <iostream>

using namespace std;

#include <iostream>
#include <cmath>

void Print_With_Probel(int arg){

for(int i=0;i<3 - std::log(arg)/std::log(10);i++){
    cout << " ";
}
cout << "  ";
cout << arg;
}

class Matrix{
public:
    int Data[100][100];
    int size_,size__;
    void get_data(){
    cin >> size_ >> size__;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            cin >> Data[i][j];
        }
    }
    }
    void get_data(int arg){
    cin >> size_;size__ = size_;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            cin >> Data[i][j];
        }
    }
    }

    void get_data(int arg,int arg2){
    cin >> size_;cin >> size__;

    }

    int get_summ(){
        int ans=0;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            ans+= Data[i][j];
        }
    }
    return ans;
    }
    int find_elem(int arg){
       int ans=0;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(arg == Data[i][j]){ans++;}
        }
    }
    return ans;
    }

    void MinAndMax(){
    int min_=Data[0][0],max_=Data[0][0];
    int min_index[2]={0,0}, max_index[2]={0,0};
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(Data[i][j] > max_){
                max_=Data[i][j];
                max_index[0]=i;max_index[1]=j;
            }

            if(Data[i][j] < min_){
                min_=Data[i][j];
                min_index[0]=i;min_index[1]=j;
            }

        }
    }
    for(int i = 0;i<size__;i++){
            int yes = 0;
        for(int j=0;j<size_;j++){
            if( Data[j][i] == max_ ){
                yes = 1;
    break;
            }
        }
        if(yes){
            for(int j=0;j<size_;j++){
                cout << Data[j][i] << " ";
            }
        }

    }
    }

    void Triangel(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(j > i){Data[i][j] = 0;}
        }

    }
    }

    void Print(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            cout << Data[i][j] << " ";
        }
        cout << endl;
    }
    }

    void IsSimmetry(){
        int da=1;
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(Data[i][j] != Data[j][i]){
                da=0;
            }
        }

    }
    if(da){
        cout << "YES";
    }else{
    cout << "NO";
    }
    }

    void Fillchess(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
           Data[i][j] = abs(i-j);
        }

    }
    }
    void RitterPrint(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            Print_With_Probel(Data[i][j]);
        }
        cout << endl;
    }
    }

    void Fill_Zmey(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
                if(j%2){
                    Data[i][j] = (j+1)*size_ -i ;
                }else{
                Data[i][j] = i+1 + size_*j;
                }
           //Data[i][j] = abs(i-j);
        }

    }
    }
    void Rotate(){
        int container[100][100];
        for(int i=0;i<size_;i++){
            for(int j=0;j<size__;j++){
                container[i][j] =  Data[size__ -j -1][i];
            }
            //cout << endl;
        }

        for(int i=0;i<size_;i++){
            for(int j=0;j<size__;j++){
                Data[i][j] =  container[i][j];
            }
            //cout << endl;
        }
    }

    int* operator[] (const int index) // для неконстантных объектов: может использоваться как для присваивания значений элементам, так и для их просмотра
    {
        return Data[index];
    }

    void fill_with_int(int num){
        for(int i=0;i<size_;i++){
            for(int j=0;j<size__;j++){
                Data[i][j] = num;
            }
            //cout << endl;
        }
    }



};

#include <iostream>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double PI = 3.14159265358979323846 ;
double ToDegree(double rad){
return rad*180/PI;
}
double ToRad(double degree){
return degree* PI/180;
}

class Point{
public:
    double X,Y;
    Point(double _X, double _Y){
        X = _X;
        Y=  _Y;
    }
    Point(){
        X = 0;
        Y=  0;
    }
    Point(double distance, double AngleRad, bool nullen){
        double sX = cos(AngleRad);
        double sY = sin(AngleRad);
        X = sX * distance;
        Y = sY * distance;
    }
    double getRotation(){
        if(Y == 0){
            if(X >= 0){
                return 0;
            }else{
                return PI;
            }
        }
        if(Y < 0 ){
            return PI * 3/2 - atan( X / Y );
        }else{
            return PI/2 - atan( X / Y );
        }
}

};
class Segment{
public:
    Point Point1, Point2;
    Segment(){
    Point1 = Point(0,0);
    Point2 = Point(1,0);
    }
    Segment(Point _Point1,Point _Point2){
    Point1 = _Point1;
    Point2 = _Point2;
    }
    Segment(double x1, double y1, double x2, double y2){
    Point1 = Point(x1,y1);
    Point2 = Point(x2,y2);
    }
    double getLength(){
        return sqrt( (Point1.X-Point2.X)*(Point1.X-Point2.X)+(Point1.Y-Point2.Y)*(Point1.Y-Point2.Y) );
    }
    double VectorDX(){return Point2.X - Point1.X; }
    double VectorDY(){return Point2.Y - Point1.Y; }

    friend Segment operator+(Segment &s1, Segment &s2){ /// Сложение Векторов в отрезок с коордами (0,0) (X,Y)
        return Segment(Point(0,0), Point( (s1.VectorDX())+(s2.VectorDX()),(s1.VectorDY())+(s2.VectorDY())));
    }

    double getScalValue(Segment s2){
    return VectorDX() * s2.VectorDX() + VectorDY() * s2.VectorDY();
    }

    double getVectValue(Segment s2){
    ///return (VectorDX() + VectorDY()) *   (s2.VectorDX() + s2.VectorDY());
    return VectorDX() * s2.VectorDY() - VectorDY()*s2.VectorDX();
    }

    void VectorStandartize(){ /// Превращение отрезка в отрезок с коордами вектора (0,0) (X,Y)
    Segment S1 = Segment(Point1,Point2);
    Segment S2 = Segment(0,0,0,0);

    Segment _test_ = S1 + S2;
    Point1 = Point(0,0);
    Point2 = _test_.Point2;
    }

};
class Angle{
public:
    double degree;
    Angle(){
    degree=90;
    }
    Angle(double _degree){
    degree= _degree;
    }

};
class Triangle{
public:
    Point Point1,Point2,Point3;
    Triangle(){
    Point1 = Point(0,0);
    Point2 = Point(1,0);
    Point3 = Point(0,1);
    }
    Triangle(Point _Point1,Point _Point2, Point _Point3){
    Point1= _Point1;
    Point2= _Point2;
    Point3= _Point3;
    }
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3){
    Point1 = Point(x1,y1);
    Point2 = Point(x2,y2);
    Point3 = Point(x3,y3);
    }
    double getPerimeter(){
    return Segment(Point1,Point2).getLength() + Segment(Point2,Point3).getLength() + Segment(Point3,Point1).getLength();
    }
    double getArea(){
        double p= getPerimeter()/2;
    return sqrt(p*(p-Segment(Point1,Point2).getLength())*(p-Segment(Point2,Point3).getLength())*(p-Segment(Point3,Point1).getLength() ));
    }



};


#include <iostream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>

#define _OPEN_SYS_ITOA_EXT
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

#include <iostream>


int main()
{
     

    int a,b,c,d;
    cin >> a >> b >> c >> d;
    Point P1(a,ToRad(b),1);
    Point P2(c,ToRad(d),1);
    Segment S(P1,P2);

    cout << fixed << setprecision(7)<< S.getLength() << endl;

    return 0;
}

