#include <cstdint>
#include <iostream>
#include <cassert>
#include <cmath>

std::istream& operator>>(std::istream& in, __int128_t &ui128) {


    std::string stream_;
    in >> stream_;

    ui128 = 0;
    for(char c : stream_){
        ui128 *= 10;
        ui128 += c-'0';
    }

    return in;

}


#include <algorithm>
///  const __uint128_t& ui128, но у меня всё деструктивно
std::ostream& operator <<(std::ostream& os, __int128_t ui128) {

    std::string buff;
    while(ui128){
        buff += (ui128%10+'0');
        ui128 /= 10;
    }



    reverse(buff.begin(),buff.end());

	return (os << buff);
}


using namespace std;

using T = __int128_t;

struct p2 {
    T x, y;
};

p2 operator+(p2 u, p2 v) {
    return {u.x + v.x, u.y + v.y};
}

p2 operator-(p2 u, p2 v) {
    return {u.x - v.x, u.y - v.y};
}

p2 operator*(p2 u, T k) {
    return {u.x * k, u.y * k};
}

T len2(p2 u) {
    return u.x * u.x + u.y * u.y;
}

T isqrt(T n) {
    T r = (T)sqrt((long double) (n));
    while (r * r > n) {
        r--;
    }
    while ((r + 1) * (r + 1) <= n) {
        r++;
    }
    return r;
}

struct P {
    T r2; // inclusive

    bool bounds_check(p2 o, p2 w) {
        T A = len2(w), B = 2 * (o.x * w.x + o.y * w.y), C = len2(o) - r2;
        T D = B * B - 4 * A * C;
        if (D < 0) {
            return true;
        }
        return B > 0 && D < B * B;
    }

    T count_segment(p2 o, p2 u, p2 v, T ulim, T vlim) {
        T ret = 0;
        while (vlim > 0) {
            if (!bounds_check(o + u * ulim, v - u)) {
                break;
            }
            ret += vlim * (vlim + 1) / 2;
            o = o + u * vlim;
            v = v - u;
            ulim -= vlim;
            if (ulim == 0) {
                return ret;
            }
            while (len2(o + v * (vlim - 1)) > r2) {
                --vlim;
            }
            if (ulim < vlim) {
                swap(u, v);
                swap(ulim, vlim);
            }
        }
        if (vlim == 0) {
            return ret;
        }
        if (vlim <= 128) {
            o = o + u * ulim;
            for (T i = 0; i < vlim; ++i) {
                while (ulim > 0 && len2(o - u) > r2) {
                    o = o - u;
                    ulim--;
                }
                ret += ulim;
                o = o + v;
            }
            return ret;
        }
        p2 w = u + v;
        T A = len2(w), B = 2 * (o.x * w.x + o.y * w.y), C = len2(o) - r2;
        T D = B * B - 4 * A * C;
        assert(D >= 0);
        T d = isqrt(D);
        T t = (-B + d) / (2 * A) + 1;
        assert(t >= 1);
        assert(t <= ulim && t <= vlim);
        ret += count_segment(o, u, w, ulim, t);
        ret += count_segment(o, v, w, vlim, t);
        ret -= t;
        return ret;
    }

    T operator()() {
        T ulim = isqrt(r2) + 1, vlim = isqrt(r2 / 2) + 1;
        T ret = count_segment({0, 0}, {1, 0}, {1, 1}, ulim, vlim);
        ret = 2 * ret - vlim;
        return ret * 4;
    }
};

int main() {
    T N;
    cin >> N;
    P p = {N * N - 1 + 1};
    T res =  p();

    /// 1 - ok
    /// 2 - (-3)
    /// 3 - (-7)
    /// 4 - (-11)
    /// 5 - (-7)
    /// 10000 - 314199016 - 314159053 = 39963

    ///cout << res << endl;
    ///cout << res/4 << endl;
    T points_cool = res/4 - (N*2 + 1);
    cout << points_cool*4 + 1 + N*4 << endl;
    return 0;
}
