///http://am-just-a-nobody.blogspot.com/2018/02/a-sub-linear-algorithm-for-gausss.html

#include <iostream>
#include <cmath>
#include <stack>
using namespace std;

template<typename T>
struct Matrix3x3{
    T a,b,c;
    T d,e,f;
    T g,h,i;
    Matrix3x3 operator* (const Matrix3x3<T>& other) const{
        return {

            a * other.a + b * other.d + c * other.g, a * other.b + b * other.e + c * other.h, a * other.c + b * other.f + c * other.i,

            d * other.a + e * other.d + f * other.g, d * other.b + e * other.e + f * other.h, d * other.c + e * other.f + f * other.i,

            g * other.a + h * other.d + i * other.g, g * other.b + h * other.e + i * other.h, g * other.c + h * other.f + i * other.i,
        };
    }
};

template<typename T>
struct Whatever{
    Matrix3x3<T> Matrix;
    int64_t w, h;

};

template<typename T>
bool isWhole(T val){
    return floorl(val) == ceill(val);
}

///
template<typename T>
int64_t gauss(int64_t n){
    int64_t sn = ceill(sqrtl(n));
    int64_t res = 0;

    stack<Whatever<int64_t>> stk;
    stk.push({ {1,0,0,  0,1,0,  0,0,-n}, sn, sn });

    while (!stk.empty()){
        /// TO-DO использовать Стак Госунова (ака просто массив)
        Whatever<int64_t> matr = stk.top();
        stk.pop();

        if ((matr.w <= 0) || matr.h <= 0)
            continue;



        int64_t a = matr.Matrix.a;
        int64_t b = matr.Matrix.b * 2;
        int64_t d = matr.Matrix.c * 2;
        int64_t c = matr.Matrix.e;
        int64_t e = matr.Matrix.f * 2;
        int64_t f = matr.Matrix.i;


        if ( (d * d - 4 * a * f < 0) || (e * e - 4 * c * f < 0) ){
            res += matr.w * matr.h;
            continue;
        }

        T x0 = ( (T(-d)) + sqrtl(d * d - 4 * a * f)) / (T(2*a));
        T y0 = ( (T(-e)) + sqrtl(e * e - 4 * c * f)) / (T(2*c));

        cout << "x0: " << x0 << endl;
        cout << "y0: " << y0 << endl;

        bool xint = isWhole(x0), yint=isWhole(y0); ///uint=0, vint=0, flag = 0;
        bool flag = 0;

        int64_t x0_c = ceill(x0);
        int64_t y0_c = ceill(y0);

        if (matr.w <= 1){
            res += (matr.h - y0_c) * matr.w - yint;
            continue;
        }

        if (matr.h <= 1){
            res += (matr.w - x0_c) * matr.h - xint;
            continue;
        }
        if (matr.w - x0 > 1){
            res += (matr.w - x0_c) * matr.h - xint;
            stk.push({matr.Matrix, x0_c, matr.h});
            continue;
        }
        if (matr.h - y0 > 1){
            res += (matr.h - y0_c) * matr.w - yint;
            stk.push({matr.Matrix, matr.w, y0_c});
            continue;
        }
        T temp = (a - b + c) * (c * d * d - b * d * e + a * e * e + b * b * f - 4 * a * c * f);
        if (temp < 0)
            continue;

        T u = ( (T) (((a - b + c) * (b * e - 2 * c * d) - (b - 2 * c) * sqrtl(temp)))) / (a - b + c) / (4 * a * c - b * b);
        bool uint = isWhole(u);

        if (u > matr.w){
            u = matr.w;
            flag = 1;
        }
        if (u < 0){
            u = 0;
            flag = 1;
        }
        temp = (e  + b * u) * (e + b * u) - 4 * c * (f + u * (d + a * u));
        cout << "temp2: " << temp << endl;
        if (temp < 0)
            continue;

        T v = ( (T) (  (- e - b * u + sqrtl(temp)))) / (T(2*c)) ;
        cout << "v: " << v << endl;
        bool vint = isWhole(v);

        if (v < 0)
            v = 0;

        int64_t u_c = ceill(u);
        int64_t v_c = ceill(v);
        if (u_c == matr.w && v_c == matr.h)
            continue;
        if (uint == 1 && vint == 1 && flag == 0)
            res -= 1;
        res += (matr.w - u_c + matr.h - 1 - v_c) * (matr.w - u_c + matr.h - v_c) / 2;

        Matrix3x3<int64_t> al = {1,0,0,  -1, 1, 0,  matr.h-v_c, v_c, 1};
        Matrix3x3<int64_t> ak = {1, -1, matr.h-v_c,  0,1,v_c,  0,0,1};

        stk.push( { (al * matr.Matrix) * ak, u_c - (matr.h - v_c), matr.h - v_c  });

        Matrix3x3<int64_t> bl = {1,-1,0,  0,1,0,  u_c, matr.w-u_c, 1};
        Matrix3x3<int64_t> bk = {1,0,u_c,  -1, 1, matr.w - u_c, 0,0,1};


        stk.push({(bl * matr.Matrix) * bk, matr.w - u_c, v_c - (matr.w - u_c)});
    }
    res = (sn - 1) * (sn - 1) - res;
    res += sn - 1;
    res *= 4;
    res += 1;
    if (sn * sn == n){
        res += 4;
    }
    return res;
}

int main(){
    cout << "INT" << endl;
    int64_t r;
    cin >> r;

    if (r == 0){
        cout << 1;
        return 0;
    }


    if (r == 1){
        cout << 5;
        return 0;
    }

    cout << gauss<long double>( r*r );
    return 0;

}
