#include "Triangle.h"


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

    /// -1 - бесконечно, 0 - нет пересечений, 1 - одно, 2 - два
    pair<int, pair<Point,Point>> intersection (Line second){



        second.move_by(Center*(-1));

        //cout << "second: " << second << endl;
        double r=radius, a=second.A, b=second.B, c=second.C; // входные данные

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
            // Центры совпадают
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
