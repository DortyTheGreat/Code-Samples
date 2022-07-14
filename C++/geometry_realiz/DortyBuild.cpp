/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: �����#9030 
---Original---Code---

#include <iostream>
#include <iomanip>
using namespace std;
//Clock MainClock;
#include "../DortyLibs/DortyBuild.h"

#include "../DortyLibs/DortyGeometry.h"


using namespace std;

int main()
{
    AppBuild();
    Triangle A;
    cin >> A;
    cout << fixed << setprecision(9) << A.getMedianCross();




    return 0;
}

*/
#include <iostream>
#include <iomanip>
using namespace std;
//Clock MainClock;


#include <cmath>


const double PI = 3.14159265358979323846 ;

double Epsilon = 0.00001;
bool doubleEqual(double a, double b){
    return (abs(a-b) <= Epsilon);
}


double ToDegree(double rad){
    return rad*180/ PI;
}
double ToRad(double degree){
    return degree* PI/180;
}


class Angle{
public:
    double radian;
    Angle(){
        radian=PI;
    }
    Angle(double _radian){
        radian = _radian;
    }

    bool isReverse(Angle angle_){
        return doubleEqual(radian+PI, angle_.radian) || doubleEqual(radian-PI, angle_.radian);
    }

};


///Dorty Utility
void YesNo(bool arg){
    if (arg){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
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

    bool operator== (Point second){
        return (X==second.X) && (Y == second.Y);
    }

    Point operator+(Point second){
        return Point(X+second.X,Y+second.Y);
    }

    Point operator-(Point second){
        return Point(X-second.X,Y-second.Y);
    }

    Point operator*(double mult){
        return Point(X*mult,Y*mult);
    }

    Point operator/(double mult){
        return Point(X/mult,Y/mult);
    }

    // vector
    double operator^(const Point &p) const {
        return X * p.Y - p.X * Y;
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
    friend istream& operator>> (std::istream &in, Point &point)
    {
        // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
        // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
        in >> point.X;
        in >> point.Y;

        return in;
    }

    friend ostream& operator<< (std::ostream &out, const Point &point)
    {
        // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
        out << point.X << " " << point.Y;

        return out;
    }

};



class Line{
public:
    double A,B,C;

    friend istream& operator>> (std::istream &in, Line &line)
    {
        // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
        // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
        in >> line.A;
        in >> line.B;
        in >> line.C;

        return in;
    }

    friend ostream& operator<< (std::ostream &out, const Line &line)
    {
        // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
        out << line.A << " " << line.B << " " << line.C;

        return out;
    }

    bool operator|| (const Line &line){
        return (doubleEqual(A*line.B,B*line.A));
    }

    bool operator== (const Line &line){
        if (*this||line){
            if (doubleEqual(B,0)){
                return doubleEqual(C/A,line.C/line.A);
            }else{
                return doubleEqual(C/B,line.C/line.B);
            }
        }
        return false;
    }

    Line(Point first, Point second){
        double dX = second.X - first.X;
        double dY = second.Y - first.Y;

        A = dY;
        B = -1 * dX;
        C = first.Y*dX - first.X * dY;

        if (!doubleEqual(dX,0)){
            ///Нормальная, меняется по иксу

        }else{
            /// ненормальная, вертикальная
        }

    }


    Line(){
        A = 1;
        B = 1;
        C = 0;
    }

    Line(double A_, double B_, double C_){
        A = A_;
        B = B_;
        C = C_;
    }

    double getY_byX(double X){
        double template_null = 1337;
        if (!doubleEqual(B,0)){
            ///Нормальная, меняется по иксу
            return -1 * (A*X + C)/B;

        }else{

            return template_null;

        }
    }

    int which_side(Point point){

        if (!doubleEqual(B,0)){
            ///Нормальная, меняется по иксу
            double Y_ = getY_byX(point.X);
            return (Y_ > point.Y);

        }else{
            ///cout << "here" << endl;
            ///return template_null;
            double x_coord = -1 * C / A;
            ///cout << x_coord << " " << point.X << " "<< (point.X > x_coord) << endl;
            return (point.X > x_coord);

            /// ненормальная, вертикальная
        }


    }

    bool DoesContainPoint(Point point){

        if (!doubleEqual(B,0)){
            ///Нормальная, меняется по иксу
            double Y_ = getY_byX(point.X);
            return doubleEqual(Y_,point.Y);

        }else{
            ///cout << "here" << endl;
            ///return template_null;
            double x_coord = -1 * C / A;
            ///cout << x_coord << " " << point.X << " "<< (point.X > x_coord) << endl;
            return doubleEqual(point.X, x_coord);

            /// ненормальная, вертикальная
        }


    }

    double distance_to_point(Point point_){
        return abs(A*point_.X + B*point_.Y + C)/(sqrt(A*A+B*B));
    }

    /// 1 - ровно в одной точке, 0 - нет пересечений, 2 - всё пересекается
    pair<int, Point> intersection(Line another_line){

        if (*this||another_line){
            return make_pair((*this==another_line)*2,Point());
        }else{
            double x_coord = (C*another_line.B-another_line.C*B)/ (another_line.A * B - A* another_line.B);
            if (doubleEqual(B,0)){
                return make_pair(1,Point(x_coord, another_line.getY_byX(x_coord)));
            }else{
                return make_pair(1,Point(x_coord, getY_byX(x_coord)));
            }
        }
    }

    void make_perpendicular_to_point(Point point_){
        swap(A,B);
        B *= (-1);
        if (doubleEqual(A,0)){
            B *= -1;
            C = (-1) * (point_.Y * B);
            return;
        }
        double MyY = getY_byX(point_.X);

        if (doubleEqual(B,0)){
            C = (-1) * (point_.X * A);
            return;
        }


            C = C + (MyY - point_.Y)*B;



    }

    void make_paralel_to_point(Point point_){
        if (doubleEqual(A,0)){
            B *= -1;
            C = (-1) * (point_.Y * B);
            return;
        }
        double MyY = getY_byX(point_.X);

        if (doubleEqual(B,0)){
            C = (-1) * (point_.X * A);
            return;
        }


            C = C + (MyY - point_.Y)*B;



    }

    void move_by(Point point_){

        if (doubleEqual(B,0)){
            // Вертикальная

            C = C + point_.X * A * (-1);
            return;
        }

        double MyY = getY_byX(0);
        make_paralel_to_point(Point(point_.X, MyY+point_.Y));

    }

};



class Segment{
public:
    Point Point1, Point2;

    friend istream& operator>> (std::istream &in, Segment &segment)
    {
        // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
        // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
        in >> segment.Point1.X;
        in >> segment.Point1.Y;

        in >> segment.Point2.X;
        in >> segment.Point2.Y;

        return in;
    }

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

    Angle getRotation(){
        Segment S2;
        S2 = *this;
        S2.VectorStandartize();
        return S2.Point2.getRotation();
    }

    bool DoesContainPoint(Point P1){
        if ( (Point1 == P1) || (Point2 == P1) ){return 1;}

        Segment S2(Point1,P1), S3(Point2,P1);

        return S2.getRotation().isReverse(S3.getRotation());

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

    double distance_to_point(Point point_){

            Line nap_line(Point1,Point2);

            double a = Segment(point_,Point1).getLength();
            double c = Segment(point_,Point2).getLength();
            double b = getLength();

            double v1 = (a*a+b*b-c*c)/(2*a*b);
            double v2 = (c*c + b*b - a*a)/(2*b*c);
            if ((v1 > 0) && (v2 > 0)){
                return nap_line.distance_to_point(point_);
            }else{
                return min(a,c);
            }

    }

};

Line seg_to_line(Segment s){
    return Line(s.Point1,s.Point2);
}

/// Высота к прямой через точку
Segment Altitude(Line A, Point B){
    Line cp = A;
    cp.make_perpendicular_to_point(B);



    return Segment(B,cp.intersection(A).second);
}


class Triangle{
public:
    Point Point1,Point2,Point3;
    Triangle(){
    Point1 = Point(0,0);
    Point2 = Point(1,0);
    Point3 = Point(0,1);
    }

    friend istream& operator>> (std::istream &in, Triangle &tr)
    {
        // ��������� operator>> �������� ������ ������ Point, �� �� ����� ������ ������ � ������ Point.
        // �������� ��������, �������� point (������ ������ Point) ������ ���� �������������, ����� �� ����� ����������� �������� ����� ������
        in >> tr.Point1;
        in >> tr.Point2;
        in >> tr.Point3;


        return in;
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


    Point getAltitudeCross(){
        Line L1 = seg_to_line(Altitude(Line(Point1,Point2),Point3));
        Line L2 = seg_to_line(Altitude(Line(Point2,Point3),Point1));
        return L1.intersection(L2).second;
    }

    Point getMedianCross(){
        Line L1 = Line(Point1, (Point2+Point3)/2 );
        Line L2 = Line(Point2, (Point3+Point1)/2 );
        return L1.intersection(L2).second;
    }



};



class Circle{
public:
    Point Center;
    double radius;

    Circle(Point centre, double radia){
        Center = centre;
        radius = radia;
    }

    Circle(){
        Center = Point(0,0);
        radius = 1;
    }

    friend istream& operator>> (std::istream &in, Circle &circl)
    {
        in >> circl.Center;
        in >> circl.radius;

        return in;
    }

    const double EPS = 0.001;

    /// -1 - ����������, 0 - ��� �����������, 1 - ����, 2 - ���
    pair<int, pair<Point,Point>> intersection (Line second){



        second.move_by(Center*(-1));

        //cout << "second: " << second << endl;
        double r=radius, a=second.A, b=second.B, c=second.C; // ������� ������

        double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);

        //cout << abs (c*c - r*r*(a*a+b*b)) << endl;

        if (  c*c > r*r*(a*a+b*b)+EPS ){
          return make_pair(0,make_pair(Point(),Point()));
        }



        if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
            return make_pair(1,make_pair(Point(x0,y0)+Center ,Point()));
        }



            double d = r*r - c*c/(a*a+b*b);
            double mult = sqrt (d / (a*a+b*b));
            double ax,ay,bx,by;
            ax = x0 + b * mult;
            bx = x0 - b * mult;
            ay = y0 - a * mult;
            by = y0 + a * mult;
            return make_pair(2,make_pair(Point(ax,ay)+Center,Point(bx,by)+Center));

    }

    pair<int, pair<Point,Point>> intersection (Circle second){

        second.Center = second.Center + Center*(-1);
        if (doubleEqual(0,second.Center.X) && doubleEqual(0,second.Center.Y)){
            // ������ ���������
            if (doubleEqual(radius,second.radius)){
                return make_pair(-1,make_pair(Point(),Point()));
            }

            return make_pair(0,make_pair(Point(),Point()));
        }

        //cout << Center << " : " << second.Center  << endl;

        double x2 = second.Center.X;
        double y2 = second.Center.Y;
        double r1 = radius;
        double r2 = second.radius;
        //cout << "CR:" << x2*x2 + y2*y2 + r1*r1 - r2*r2 << endl;
        //cout << "Line: " << Line(-2*x2,-2*y2,x2*x2 + y2*y2 + r1*r1 - r2*r2) << endl;
        pair<int, pair<Point,Point>> ans =  second.intersection(Line(-2*x2,-2*y2,x2*x2 + y2*y2 + r1*r1 - r2*r2));
        ans.second.first = ans.second.first + Center;
        ans.second.second = ans.second.second + Center;

        return ans;
    }


    pair<int, pair<Point,Point>> tangent_to(Point point_){
        Line Ex;

        double x0 = 0;
        double x1 = point_.X - Center.X;

        double y0 = 0;
        double y1 = point_.Y - Center.Y;

        Ex.A = - x0 - x1;
        Ex.B = - y0 - y1;
        Ex.C = radius*radius + x0*x1 + y0 * y1;

        pair<int, pair<Point,Point>> ans = Circle(Point(0,0),radius).intersection(Ex);

        ans.second.first = ans.second.first + Center;
        ans.second.second = ans.second.second + Center;

        return ans;

    }
};

#include <vector>
template <typename T>
int signum(T num){
    if (num < 0){return -1;}
    if (num > 0){return -1;}
    return 0;
}

class Polygon{
public:
    int size_;

    vector<Point> points;

    signed int size(){
        return size_;
    }


    /// �������� ��� ����������
    double getArea(){
        double Area = 0;
        for(int i =2;i<size_;i++){
            /// i, i+1;
            Area += Triangle(points[0],points[i-1],points[i]).getArea();
        }
        return Area;
    }

    double getRightArea(){
        double Area = 0;

            Area += points[0].X*(points[size_-1].Y - points[1].Y);
            Area += points[size_ - 1].X*(points[size_-2].Y - points[0].Y); // ���� i == n-1, �� y[i+1] �������� �� y[0]

        for(int i =1;i<size_ - 1;i++){
                Area += points[i].X*(points[i-1].Y - points[i+1].Y);
        }

        Area = abs(Area/2);
        return Area;
    }

    /// �������� ��?
    bool isConvex(){

        if (size_ < 4){
            return true;
        }

        if ( ((points[size_ - 1]-points[0])^(points[0]-points[1])) * ((points[0]-points[1])^(points[1]-points[2])) < 0 ){
                return false;
        }

        if ( ((points[size_ - 2]-points[size_ - 1])^(points[size_ - 1]-points[0])) * ((points[size_ - 1]-points[0])^(points[0]-points[1])) < 0 ){
                return false;
        }

        if ( ((points[size_ - 3]-points[size_ - 2])^(points[size_ - 2]-points[size_ - 1])) * ((points[size_ - 2]-points[size_ - 1])^(points[size_ - 1]-points[0])) < 0 ){
                return false;
        }



        for(int i =0;i<size_-3;i++){
                ///if ((points[i]^points[i+1]) * (points[i+1]^points[i+2]) <0){
                ///    return false;
                ///}

            if ( ((points[i]-points[i+1])^(points[i+1]-points[i+2])) * ((points[i+1]-points[i+2])^(points[i+2]-points[i+3])) < 0 ){
                return false;
            }
            ///cout << ((points[i]-points[i+1])^(points[i+1]-points[i+2])) << endl;
        }

        return true;
    }



    friend istream& operator>> (std::istream &in, Polygon &pg)
    {
        signed int sz;
        in >> pg.size_;
        sz = pg.size_;
        pg.points.resize(pg.size_);

        for(int i =0;i<sz;i++){
            in >> pg.points[i];
        }

        return in;
    }

    const double EPS = 0.001;

};




using namespace std;

int main()
{
     
    Triangle A;
    cin >> A;
    cout << fixed << setprecision(9) << A.getMedianCross();




    return 0;
}

