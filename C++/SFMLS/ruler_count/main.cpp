#include <iostream>
#include <set>
using namespace std;

bool correct(const set<int>& ruler, int num){
    for(int i = 0; i <= num; ++i){
        bool flag = false;
        for(const auto& elem1 : ruler){
            for(const auto& elem2 : ruler){
                if (abs(elem2 - elem1) == i ) flag = true;
            }
        }
        if (!flag) return 0;
    }
    ///cout << endl;
    ///cout << num << " : ";
    for(const auto& elem1 : ruler){
        ///cout << elem1 << " ";
    }
    ///cout << endl;
    return 1;
}

int a(int arg){
    int res = 0;
    for(int mask = 0; mask < (1 << arg); ++mask){
        set<int> ruler;
        ruler.insert(0);
        for(int bit = 0; bit < 32; ++bit){
            if ( (mask >> bit) & 1 ){
                ruler.insert(bit+1);
            }
        }
        if (correct(ruler, arg)) res++;

    }
    return res;
}

int main()
{
    for(int i = 1; i < 10; ++i){
        cout << i << " : " << a(i) << endl;
    }
    cout << "Hello world!" << endl;
    return 0;
}
