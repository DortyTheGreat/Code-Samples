/// ”гол в пространстве (имеет координаты)

class DAngle{
public:
    /// a,b в относительной форме (aka root - a, root - b)
    Point a,root,b;


    long double an_a;// = atan2(oa.Y, oa.X);
    long double an_b;// = atan2(ob.Y, ob.X);


    /// ƒанные отсортированы так, что угол к "a" меньше(в форме [0;2PI))

    DAngle(Point a_, Point mid_, Point b_) : a(a_),root(mid_),b(b_){
        a = root - a;
        b = root - b;
        an_a = atan2(a.Y, a.X);

        if (an_a < 0)
            an_a += 2*PI;

        an_b = atan2(b.Y, b.X);

        if (an_b < 0)
            an_b += 2*PI;

        if (an_b < an_a)
            swap(an_a, an_b);
    }

    bool DoesContain(Point to){

        Point op = root - to;
        long double a2 = atan2(op.Y, op.X);
        if (a2 < 0)
            a2 += 2*PI;

        /// ќбработка пограничных случаев
        if ((root == to) || doubleEqual(an_a,a2) || doubleEqual(an_b,a2)) {
            return true;
        }

        return (a2 >= an_a && a2 <= an_b) == (an_b - an_a <= PI);
    }
};
