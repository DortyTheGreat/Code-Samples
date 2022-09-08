#include <iostream>
template<typename T>
class Matrix{
private:
    T** data;
    size_t m = 0,n = 0;
public:
    Matrix(){}
    Matrix(size_t _m, size_t _n) : m(_m), n(_n){
        data = new T* [m];
        for(size_t i = 0;i<m;++i) data[i] = new T[n];
    }

    friend std::ostream& operator <<(std::ostream& os, const Matrix& matr) {
        for(size_t i = 0;i<matr.m;++i){
            for(size_t j = 0;j<matr.n;++j){
                os << matr.data[i][j] << " ";
            }
            os << '\n';
        }

        return (os);
    }


    friend std::istream& operator>>(std::istream& in, Matrix &matr) {
        in >> matr.n;
        in >> matr.m;

        for(size_t i = 0;i<matr.m;++i){
            for(size_t j = 0;j<matr.n;++j){
                in >> matr.data[i][j];
            }
        }
        return in;
    }

    Matrix operator+ ( const Matrix& other) const{
        if (n != other.n || m != other.m) return Matrix(0,0);
        Matrix ret(m,n);

        for(size_t i = 0;i<m;++i){
            for(size_t j = 0;j<n;++j){
                ret.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return ret;

    }

    Matrix operator* ( T val) const{
        Matrix ret(m,n);

        for(size_t i = 0;i<m;++i){
            for(size_t j = 0;j<n;++j){
                ret.data[i][j] = data[i][j] * val;
            }
        }
        return ret;

    }

    Matrix operator* ( const Matrix& other) const{
        if (n != other.m){ return Matrix(0,0);}

        Matrix ret(m,other.n);

        for(size_t i = 0;i<m;++i){
            for(size_t j = 0;j<other.n;++j){
                ret.data[i][j] = data[i][j] * val;
            }
        }

        return ret;

    }



};

/**
1 2 3
4 5 6

2 x 3
m x n
*/

template <typename T>
T summ(T a,T b){
    return a + b;
}


using namespace std;

int main()
{
    cout << summ(2.2,3.9) << endl;

    Matrix<int> a(10,20);
    cin >> a;
    cout << a;

    a.operator+(a)
    cout << a + Matrix(2,3) << endl;
    cout << a * 2 << endl;
    cout << "Hello world!" << endl;
    return 0;
}
