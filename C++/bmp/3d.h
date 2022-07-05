class Vector3{
public:
    long double X,Y,Z;

    Vector3() : X(0),Y(0),Z(0) {}
    Vector3(long double _X, long double _Y, long double _Z) : X(_X),Y(_Y),Z(_Z) {}
};



class Cube{
public:
    Vector3 low, high;

    Cube(){};

    Cube(Vector3 l, Vector3 h) : low(l), high(h) {}

    bool isInside(Vector3 vc){
        return (vc.X <= high.X && vc.Y <= high.Y && vc.Z <= high.Z ) && (vc.X >= low.X && vc.Y >= low.Y && vc.Z >= low.Z );
    }

};
