
#include <vector>
template<typename T>
std::vector<T> primes(T num){
    std::vector<T> ret;
    bool* _Prime = new bool[num];

    for(size_t i = 0;i<num;++i)
        _Prime[i] = 1;

    for(size_t i = 2; i<num;++i){
        if (_Prime[i]){
            ret.push_back(i);
            for(size_t j = 2*i; j<num;j+=i){
                _Prime[j] = 0;
            }
        }
    }
    return ret;
}
