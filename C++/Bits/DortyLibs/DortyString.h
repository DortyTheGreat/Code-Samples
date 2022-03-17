#include <sstream>
template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }


  template <typename T>
  basic_string<T> reverse( basic_string<T> str){
    basic_string<T> ret = "";
    size_t sz = str.size();
    for(size_t i = 0;i < sz;i++){
        ret += str[sz - i -1];
    }
    return ret;
  }
