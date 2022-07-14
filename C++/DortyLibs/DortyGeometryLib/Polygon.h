#include "Circle.h"
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


    /// Работает для невыпуклых
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
            Area += points[size_ - 1].X*(points[size_-2].Y - points[0].Y); // если i == n-1, то y[i+1] заменяем на y[0]

        for(int i =1;i<size_ - 1;i++){
                Area += points[i].X*(points[i-1].Y - points[i+1].Y);
        }

        Area = abs(Area/2);
        return Area;
    }

    /// Выпуклый ли?
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
