    #include <iostream>
    #include <cmath>
    #include <iomanip>
    using namespace std;

    ///Dorty Utility
    void YesNo(bool arg){
        if (arg){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }


    double PI = 3.14159265358979323846 ;
    double ToDegree(double rad){
        return rad*180/PI;
    }
    double ToRad(double degree){
        return degree* PI/180;
    }

    double Epsilon = 0.00001;
    bool doubleEqual(double a, double b){
        return (abs(a-b) <= Epsilon);
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

        Point operator+(Point second){
            return Point(X+second.X,Y+second.Y);
        }

        Point operator*(double mult){
            return Point(X*mult,Y*mult);
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

        double distance_to_point(Point point_){
            return abs(A*point_.X + B*point_.Y + C)/(sqrt(A*A+B*B));
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

    int main()
    {
        ///cout << DoubleEquality(1,0);
        Point a[1000];
        int n;
        cin >> n;
        for(int i =0;i<n;i++){
            cin >>a[i];
        }
        double mini_ = 1000;
        Point p1;

        Point MyCoord(0,0);
        Point poited;
        for(int itter=0;itter<1000;itter++){

                double max_dist = -1;


                /// Потом оптимизировать под макс. из массива
                for(int i =0;i<n;i++){
                        double dist = Segment(MyCoord,a[i]).getLength();
                    if (dist > max_dist){
                        max_dist = dist;
                        poited = a[i];
                    }
                }

                double proportion = 0.5/pow(1.025,itter);

                MyCoord = MyCoord * (1-proportion)  + poited * (proportion);
                if (max_dist < mini_){
                    mini_ = max_dist;
                }
            }




        cout << MyCoord << " " << mini_ << endl;

        ///cout << (p1+p2)*0.5 << " " << maxi_/2;


        return 0;
    }
