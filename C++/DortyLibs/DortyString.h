#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}


  template <typename T>
  std::basic_string<T> reverse( std::basic_string<T> str){
    std::basic_string<T> ret = "";
    size_t sz = str.size();
    for(size_t i = 0;i < sz;i++){
        ret += str[sz - i -1];
    }
    return ret;
  }


/**
vector<string> split(string s, const string& delimiter=" "){
    vector<string> ret;

    std::string token;
    for (size_t pos = 0;(pos = s.find(delimiter)) != std::string::npos;s.erase(0, pos + delimiter.length())) {
        ret.push_back(s.substr(0, pos));

    }
    ret.push_back(s);
    return ret;
}
*/
