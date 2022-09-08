#include "Point.h"


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

    Line(double A_, double B_, double C_) : A(A_), B(B_), C(C_){}

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
