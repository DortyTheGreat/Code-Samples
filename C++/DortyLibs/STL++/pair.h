#include <utility>

#ifdef _GLIBCXX_IOSTREAM
template <typename T, typename F>
std::ostream& operator<<(std::ostream &in, const std::pair<T,F> &p) {
    return (in << p.first <<' ' << p.second);
}

template <typename T, typename F>
std::istream& operator>>(std::istream& in, std::pair<T,F> &p) {
    return (in >> p.first >> p.second);
}

#endif

template <typename T, typename F>
std::pair<T,F> operator + (const std::pair<T,F>& p1,const std::pair<T,F>& p2) {
    return {p1.first+p2.first,p1.second+p2.second};
}
