#include <iostream>
#include <cmath>
#include <time.h>



#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>

class Clock2{
private:
    long long start_prog_time;
    long long last_time;



public:

    Clock2(){
        start_prog_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        last_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    void tick() {
        long long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        ///cout << CLOCKS_PER_SEC << endl;
        std::cout << (time - start_prog_time) << " (+" <<time-last_time << ")" << std::endl;
        last_time = time;
    }

    void tick(std::string text){
        std::cout << text << " : ";
        tick();
    }


};

Clock2 MainClock;




#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

uint64_t get_nanoseconds() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

class Clock{
    uint64_t p_time = 0;
    public:
    uint64_t temp_val;
    uint64_t copy;
    public:
    uint64_t tick(){
        temp_val = get_nanoseconds();
        copy = p_time;
        p_time = temp_val;
        return temp_val - copy;
    }

    Clock(){
        p_time = get_nanoseconds();
        std::cout << "ini" << std::endl;
    }

};
///uint64_t Clock::temp_val = 0;
///uint64_t Clock::copy = 0;
using namespace std;

unsigned short rand16(){return rand();}
unsigned int rand32(){return (unsigned int)(rand16()) * 65535 + rand16();}
unsigned long long rand64(){return (unsigned long long)(rand32()) * 0xffffffff + rand32();}
__uint128_t rand128(){return (__uint128_t)(rand64()) * 0xffffffffffffffff + rand64();}

#define t10(a) a a a a a a a a a a

#define t50(a) a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a

__forceinline long long mul(const long long& a,const long long& b){
    return a * b;
}

uint64_t montmul(__uint128_t a, uint64_t b, uint64_t mod, uint64_t inv){
    a *= b;
    uint64_t y = (a >> 64) - (__uint128_t(uint64_t(a) * inv) * mod >> 64);
    return int64_t(y) < 0 ? y + mod : y;

}

__forceinline uint64_t montmul_i(const __uint128_t& a, const __uint128_t& b){
    return a * b;


}

int main()
{



    Clock cl;
    cl.tick();

    const int itterations = 10000;
    const int rerand_i = 1000;

    for(int i = 0;i<itterations;++i){
        int a = rand(),b = rand(),c;
        for(int j = 0;j<rerand_i;++j){
            t10(c = a * b;)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10 << " ns - int mult" << endl;

    for(int i = 0;i<itterations;++i){
        long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            t10(c = a * b;)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10 << " ns - long long mult" << endl;

    for(int i = 0;i<itterations;++i){
        long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            t10(c = mul(a, b);)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10 << " ns - long long mult(func)" << endl;

    for(int i = 0;i<itterations;++i){
        uint64_t a = rand64(),b = rand64(),c, d = rand64(), e = rand64();
        for(int j = 0;j<rerand_i;++j){
            t10(c = montmul(a, b,c,d);)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10 << " ns - mont mul" << endl;

    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            t10(c = montmul_i(a, b);)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10 << " ns - mont mul_i" << endl;

    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand128(),b = rand128(),c;
        for(int j = 0;j<rerand_i;++j){
            t10(c = a * b;)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10  << " ns - u128 mult" << endl;

    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand128(),b = rand128(),c;
        for(int j = 0;j<rerand_i;++j){
            t10(c = a * b;)
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i / 10  << " ns - bigger u128 mult" << endl;

    for(int i = 0;i<itterations;++i){
        int a = rand(),b = rand() + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a / b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - int div" << endl;

    for(int i = 0;i<itterations;++i){
        long long a = rand(),b = rand() + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a / b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - long long div" << endl;

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand(),b = rand() + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a / b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - unsigned long long div" << endl;


    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand() + rand() * 32767,b = rand() + rand() * 32767 + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a / b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - bigger u128 div" << endl;

    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand128(),b = rand64() + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a / b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - even bigger u128 div" << endl;

    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand128(),b = rand64() + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a %  b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - even bigger u128 remainder" << endl;


    for(int i = 0;i<itterations;++i){
        __uint128_t a = rand128(),b = rand128() + 1,c;
        for(int j = 0;j<rerand_i;++j){
            c = a / b;
        }
    }

    cout << double(cl.tick()) / itterations / rerand_i << " ns - even even bigger u128 div" << endl;






    cout << "Hello world!" << endl;
    return 0;
}
