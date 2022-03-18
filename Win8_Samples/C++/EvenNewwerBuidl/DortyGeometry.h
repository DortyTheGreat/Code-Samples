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

