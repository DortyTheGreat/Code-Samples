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
    return floor(val) == ceil(val);
}

///
template<typename T>
int64_t gauss(int64_t n){
    int64_t sn = ceil(sqrtl(n));
    int64_t res = 0;

    stack<Whatever<T>> stk;
    stk.push({ {1,0,0,  0,1,0,  0,0,-n}, sn, sn });

    while (!stk.empty()){
        /// TO-DO использовать Стак Госунова (ака просто массив)
        Whatever<T> matr = stk.top();
        stk.pop();

        if ((matr.w <= 0) || matr.h <= 0)
            continue;

        T a = matr.Matrix.a;
        T b = matr.Matrix.b * 2;
        T d = matr.Matrix.c * 2;
        T c = matr.Matrix.e;
        T e = matr.Matrix.f * 2;
        T f = matr.Matrix.i;


        if ( (d * d - 4 * a * f < 0) || (e * e - 4 * c * f < 0) ){
            res += matr.w * matr.h;
            continue;
        }

        T x0 = (- d + sqrtl(d * d - 4 * a * f)) / 2 / a;
        T y0 = (- e + sqrtl(e * e - 4 * c * f)) / 2 / c;

        cout << "x0: " << x0 << endl;
        cout << "y0: " << y0 << endl;

        int64_t x0_c = ceill(x0);
        int64_t y0_c = ceill(y0);

        bool xint = isWhole(x0), yint=isWhole(y0); ///uint=0, vint=0, flag = 0;
        bool flag = 0;

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
            stk.push({matr.Matrix, ceil(x0), matr.h});
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

        T u = ((a - b + c) * (b * e - 2 * c * d) - (b - 2 * c) * sqrtl(temp)) / (a - b + c) / (4 * a * c - b * b);
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

        T v = (- e - b * u + sqrtl(temp)) / 2 / c;
        cout << "v: " << v << endl;
        bool vint = isWhole(v);

        if (v < 0)
            v = 0;

        int64_t u_c = ceill(u);
        int64_t v_c = ceill(v);

        if (u == matr.w && v == matr.h)
            continue;
        if (uint == 1 && vint == 1 && flag == 0)
            res -= 1;
        res += floor((matr.w - u + matr.h - 1 - v) * (matr.w - u + matr.h - v) / 2);

        Matrix3x3<T> al = {1,0,0,  -1, 1, 0,  matr.h-v_c, v_c, 1};
        Matrix3x3<T> ak = {1, -1, matr.h-v_c,  0,1,v_c,  0,0,1};

        stk.push( { (al * matr.Matrix) * ak, u_c - (matr.h - v_c), matr.h - v_c  });

        Matrix3x3<T> bl = {1,-1,0,  0,1,0,  u_c, matr.w-u_c, 1};
        Matrix3x3<T> bk = {1,0,u_c,  -1, 1, matr.w - u_c, 0,0,1};


        stk.push({(bl * matr.Matrix) * bk, matr.w - u_c, v_c - (matr.w - u_c)});


        stk.push({(bl * matr.Matrix) * bk, matr.w - u, v - (matr.w - u)});
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
    cout << "double" << endl;
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
