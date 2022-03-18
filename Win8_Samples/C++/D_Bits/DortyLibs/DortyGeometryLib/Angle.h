#include "GeometryBasics.h"

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
