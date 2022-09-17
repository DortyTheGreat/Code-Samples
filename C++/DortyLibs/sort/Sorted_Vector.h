#include <vector>
#include <algorithm>

template<typename T>
class Sorted_Vector{
public:
    std::vector<T> data;
    Sorted_Vector(std::vector<T> vec){
        std::sort(vec.begin(), vec.end());
        data = vec;
    }

    size_t count_elems_lower(const T& elem){
        return std::lower_bound(data.begin(), data.end(), elem) - data.begin();
    }
};
