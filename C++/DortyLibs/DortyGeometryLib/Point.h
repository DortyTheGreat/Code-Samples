#include "Angle.h"







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
    friend std::istream& operator>> (std::istream &in, Point &point)
    {
        return in >> point.X >> point.Y;
    }

    friend std::ostream& operator<< (std::ostream &out, const Point &point)
    {
        return out << point.X << " " << point.Y;
    }

};
