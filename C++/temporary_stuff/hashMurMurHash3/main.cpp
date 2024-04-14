#include <iostream>
#include <cstdint>

using namespace std;


#include <algorithm>
std::ostream& operator <<(std::ostream& os, __uint128_t ui128) {

    string buff;
    while(ui128){
        buff += (ui128%10+'0');
        ui128 /= 10;
    }
    reverse(buff.begin(),buff.end());

	return (os << buff);
}

int main()
{
    __uint128_t summ = 0;
    uint64_t start, shift, mult, n;


    cin >> start >> shift >> mult >> n;

    for(int i = 0; i < n; ++i){
        start = ((start >> shift) ^ start) * mult;
        summ += start;
    }

    cout << summ << endl;

    return 0;
}
