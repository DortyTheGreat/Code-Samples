
# if defined(NOD)
#else
long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   while(1){
        a=a%b;
        if(a==0){break;}else{if(a<b){swap(a,b);}}
   }
  return b;

}
# endif // NOD
/// комментарий
class Rational{
public:
    long long numerator = 0;
    long long denominator = 1;

    void stabilize(){
        long long nod_ = NOD(numerator,denominator);
        numerator /= nod_;
        denominator /= nod_;
    }

    Rational operator+(Rational r){

        Rational ret(numerator*r.denominator + denominator*r.numerator,denominator*r.denominator);
        ret.stabilize();

        return ret;
    }

    template <typename T>
    Rational(T num, T den){
        numerator = num;
        denominator = den;
    }

    Rational() : numerator(0),denominator(1){}




    friend istream& operator>> (std::istream &in, Rational &r)
    {
        in >> r.numerator;
        in >> r.denominator;


        return in;
    }

    friend ostream& operator<< (std::ostream &out, const Rational &r)
    {
        // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
        out << r.numerator << " " << r.denominator;

        return out;
    }

};
