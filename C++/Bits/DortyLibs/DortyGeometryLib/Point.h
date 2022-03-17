#include "Angle.h"

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
