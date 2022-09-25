#include <vector>

template<typename T>
class PrefixSum{
public:
    std::vector<T> data;
    PrefixSum(std::vector<T> arr){
        if (arr.size() == 0) return;
        data.resize(arr.size());
        data[0] = arr[0];
        for(size_t i = 1;i<arr.size();++i){
            data[i] = data[i-1] + arr[i];
        }
    }

    T get_summ(size_t start, size_t end){
        if (start == 0) return data[end];
        return data[end] - data[start-1];
    }
};
