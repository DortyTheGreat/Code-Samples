#include "../gcd.h"
#include <vector>
#include <set>

template<typename T>
class Rational{
public:
    T numerator = 0;
    T denominator = 1;
    char separator = '/';

    void stabilize(){
        T nod_ = gcd(numerator,denominator);
        numerator /= nod_;
        denominator /= nod_;
    }

    Rational operator+(const Rational& r) const{

        Rational ret(numerator*r.denominator + denominator*r.numerator,denominator*r.denominator);
        ret.stabilize();

        return ret;
    }

    bool operator<(const Rational& r) const{
        return (long double)(numerator) / denominator < (long double)(r.numerator) / r.denominator;
    }

    template <typename F>
    Rational(F num, F den) : numerator(num), denominator(den){stabilize();}

    Rational() : numerator(0),denominator(1){}




    friend std::istream& operator>> (std::istream &in, Rational &r)
    {
        in >> r.numerator;
        in >> r.denominator;


        return in;
    }

    friend std::ostream& operator<< (std::ostream &out, const Rational &r)
    {
        // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
        out << r.numerator << r.separator << r.denominator;

        return out;
    }

    template<typename F>
    static std::set< Rational<F> > get_all_fractions(F number){
        std::set< Rational<T> > ret;
        for(F i = 1; i <= number;++i){
            for(F j = i+1; j <= number;++j){
                ret.insert({i,j});
            }
        }
        return ret;
    }

    /// https://stepik.org/lesson/668294/step/3?unit=666389
    template<typename F>
    static std::vector< Rational<F> > get_all_fractions_stepik(F number){
        std::vector< Rational<T> > ret;
        for(F i = 2; i <= number;++i){
            for(F j = 1; j < i;++j){
                if (gcd(i,j) == 1) ret.push_back({j,i});
            }
        }
        return ret;
    }

};

