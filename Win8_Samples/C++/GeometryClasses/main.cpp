#include <iostream>
#include <cmath>
#include <iomanip>

///======
///
///
///Работа была: 05.11.2020, 24.07.2021, 30.09.2021
///=====

#define double long double


using namespace std;
double PI = 3.14159265358979323846 ;
double ToDegree(double rad){
return rad*180/PI;
}
double ToRad(double degree){
return degree* PI/180;
}

double Epsilon = 0.0000000000000001;

bool doubleEqual(double d1, double d2){
    return (abs(d1 - d2) < Epsilon);

}

class Angle{
public:
    double degree;
    Angle(){
    degree=90;
    }
    Angle(double _degree){
    degree= _degree;
    }

    friend std::ostream& operator<< (std::ostream &out, const Angle &angle_){

        // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
        out << angle_.degree;

        return out;
    }

    bool isReverse(Angle angle_){
    return doubleEqual(degree+180, angle_.degree) || doubleEqual(degree-180, angle_.degree);
    }

};

class Point{
public:
double X,Y;
Point(double _X, double _Y){
X = _X;
Y=  _Y;
}

bool operator== (Point second){
return (X==second.X) && (Y == second.Y);
}

void read(){
cin >> X >> Y;
}
Point(){
X = 0;
Y=  0;
}
Angle getRotation(){
if(Y == 0){
    if(X >= 0){
        return Angle(0);
    }else{
    return Angle(180);
    }
}
if(Y < 0 ){
    return Angle(180 + atan( X / Y ) * 180 / 3.14159265);
}
if(X > 0){
     return Angle(atan( X / Y ) * 180 / 3.14159265);
}else{
    return Angle(360 + atan( X / Y ) * 180 / 3.14159265);
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
    void read(){
    Point1.read();Point2.read();
    }

    bool DoesContainPoint(Point P1){
        if ( (Point1 == P1) || (Point2 == P1) ){return 1;}

        Segment S2(Point1,P1), S3(Point2,P1);

        return S2.getRotation().isReverse(S3.getRotation());

    }

    void SwapPoints(){
    swap(Point1,Point2);
    }

    Angle getRotation(){
        Segment S2;
        S2 = *this;
        S2.VectorStandartize();
        return S2.Point2.getRotation();
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
    void read(){
    Point1.read();Point2.read();Point3.read();
    }
    double getPerimeter(){
    return Segment(Point1,Point2).getLength() + Segment(Point2,Point3).getLength() + Segment(Point3,Point1).getLength();
    }
    double getArea(){
        double p= getPerimeter()/2;
    return sqrt(p*(p-Segment(Point1,Point2).getLength())*(p-Segment(Point2,Point3).getLength())*(p-Segment(Point3,Point1).getLength() ));
    }



};
int main()
{
    Segment S1,S2;
    S1.read();
    S2.read();

    Triangle T1(S1.Point1,S1.Point2,S2.Point1),T2(S1.Point1,S1.Point2,S2.Point2);

    Triangle T3(S2.Point1,S2.Point2,S1.Point1),T4(S2.Point1,S2.Point2,S1.Point2);

    double S_1 = T1.getArea() + T2.getArea();

    double S_2 = T3.getArea() + T4.getArea();

    if( doubleEqual(S_1,S_2)){
        cout << "YES";
    }else{
        cout << "NO";
    }


}
