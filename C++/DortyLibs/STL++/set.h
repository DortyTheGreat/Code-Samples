#include <set>
#ifdef  _GLIBCXX_IOSTREAM

template <typename T>
std::ostream& operator<<(std::ostream &out, const std::set<T> &st) {
    for(auto elem : st){
        out << elem << ' ';
    }

    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, std::set<T> &st) {
    size_t size_ = st.size();
    if (size_ == 0)
        in >> size_;
    st.resize(size_);

    for(int i = 0;i<size_;i++){
        T val;
        in >> val;
        st.insert(val);
    }

    return in;
}

template <typename T>
void read(std::set<T> &st, size_t sz){
    for(size_t i =0;i<sz;++i){
        T val;
        std::cin >> val;
        st.insert(val);
    }
}

template <typename T>
void read(std::multiset<T> &st, size_t sz){
    for(size_t i =0;i<sz;++i){
        T val;
        std::cin >> val;
        st.insert(val);
    }
}


#endif

template <typename T>
bool contains(const std::set<T>& st, const T& elem){
    return st.find(elem) != st.end();
}

/// not tested
#include <utility>
template <typename T>
std::pair<size_t,size_t> indexOf(const std::multiset<T>& mst, const T& elem){
    auto lb = std::distance(mst.begin(),mst.lower_bound (elem));
    if (lb == mst.size()) return {-1,-1};
    return {lb,std::distance(mst.begin(),mst.upper_bound (elem))-1} ;
}

/*
template <typename T>
void operator += (std::vector<T> &vect,T number) {
    vect.push_back(number);
}



template <typename T>
std::vector<T> get_all_sub_strings(T &vect){

    std::vector<T> ret;

    int sz = vect.size();

    for(int l = 0;l<sz;l++){
        for(int r = l+1;r<sz+1;r++){
            T obj;
            for(int cou = l;cou < r;cou ++){
                obj += vect[cou];
            }
            ret.push_back(obj);

        }
    }

    return ret;
}




template <typename T>
T sum(std::vector<T> &vect){
    T ret = 0;
    int sz = vect.size();
    for(int l = 0;l<sz;l++){
        ret += vect[l];
    }
    return ret;
}

template <typename T>
T min(std::vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = std::min(ret,vect[i]);
    }
    return ret;
}

template <typename T>
T max(std::vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = std::max(ret,vect[i]);
    }
    return ret;
}

#ifdef _GLIBCXX_STRING
template <typename T>
std::vector<T> list(std::basic_string<T> str){
    std::vector<T> ret;
    ret.resize(str.size());
    for(size_t i = 0;i<str.size();i++){
        ret[i] = str[i];
    }
    return ret;
}
#endif // _GLIBCXX_STRING
template <typename T>
inline T first(std::vector<T> &vect){
    return vect[0];
}

template <typename T>
inline T last(std::vector<T> &vect){
    return vect[vect.size() - 1];
}

*/
