#include "Segment.h"

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
        // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
        // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
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
