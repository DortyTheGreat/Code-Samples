#include "Line.h"


class Segment{
public:
    Point Point1, Point2;

    friend std::istream& operator>> (std::istream &in, Segment &segment)
    {
        return in >> segment.Point1 >> segment.Point2;
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
                return std::min(a,c);
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
