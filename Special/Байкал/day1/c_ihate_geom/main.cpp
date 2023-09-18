#include <iostream>

#include <cmath>


const double PI = 3.14159265358979323846 ;

double Epsilon = 0.00001;
bool doubleEqual(double a, double b){
    return (abs(a-b) <= Epsilon);
}

double getY_byX(double X, double A, double B, double C){
    if (!doubleEqual(B,0)){

        return -1 * (A*X + C)/B;
    }else{
        return -1337.3;
    }
}

using namespace std;

int main()
{








    int x1,y1, x2,y2;
    int x3,y3, x4,y4;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    double dX = x2 - x1;
    double dY = x2 - x1;

    double A1 = dY;
    double B1 = -1 * dX;
    double C1 = y1*dX - x1 * dY;


    if (A1 == 0 && B1 == 0){

    }

    dX = x4 - x3;
    dY = x4 - x3;

    double A2 = dY;
    double B2 = -1 * dX;
    double C2 = y3*dX - x3 * dY;


    if (doubleEqual(A1*B2,B1*A2)){



        bool equal_ = false;
        if (doubleEqual(B1,0)){
            equal_= doubleEqual(C1/A1,C2/A2);
        }else{
            equal_ = doubleEqual(C1/B1,C2/B2);
        }

        if (equal_ == false){
            /// они паралельны, но не равны
            cout << "NO";
            return 0;
        }
        if ( x1 <= max(x3,x4) && x1 >= min(x3,x4) ){
            cout << "YES";
            return 0;
        }

        if ( x2 <= max(x3,x4) && x2 >= min(x3,x4) ){
            cout << "YES";
            return 0;
        }

        cout << "NO";
        return 0;
    }



    double x_coord = (C1*B2-C2*B1)/ (A2 * B1 - A1* B2);
    double y_coord;
    if (doubleEqual(B1,0)){
        y_coord = getY_byX(x_coord, A2, B2, C2);
    }else{
        y_coord = getY_byX(x_coord, A1, B1, C1);
    }

    if ( x_coord > max(x3,x4) || x_coord < min(x3,x4) ){
        cout << "NO";
        return 0;
    }

    if ( x_coord > max(x1,x2) || x_coord < min(x1,x2) ){
        cout << "NO";
        return 0;
    }

    if ( y_coord > max(y3,y4) || x_coord < min(y3,y4) ){
        cout << "NO";
        return 0;
    }

    if ( y_coord > max(y1,y2) || y_coord < min(y1,y2) ){
        cout << "NO";
        return 0;
    }

     cout << "YES";
    return 0;

}
