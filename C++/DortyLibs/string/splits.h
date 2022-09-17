/**
ex:
"abbbbaaaaccdddee" ->
["a","bbbb", "aaaa", "cc", "ddd", "ee"]
*/

#include <vector>


std::vector<std::string> split_by_repeting_symbols(const std::string& a){

    std::vector<std::string> ret;
    if (a.empty()) return ret;
    ret.push_back(std::string(1,a[0]));

    for(int i = 1;i< a.size();++i){
        if (a[i] != ret.back().back() ){
            ret.push_back(std::string(1,a[i]));
        }else{
            ret.back() += a[i];
        }
    }
    return ret;


}
