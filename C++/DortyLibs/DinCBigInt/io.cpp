
#include <algorithm> /// для реверса string

char FromIntToChar(int a){
    if (a >= 0 && a <= 10){
        return (a + '0');
    }
    return (a - 10) + 'A';
}

int FromCharToInt(char a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }
    return (a - 'A')+10;
}

// печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const BigUnsigned& bi) {
	/*
	if ( (bi._digits.size() == 1) && (bi._digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }
    */



    CONT_TYPE Carret;
    std::string buff = "";
    for(int i = 0;i<bi.real_size;++i){
        Carret = bi._digits[i];
        for(int j = 0; j < cnt_stack;++j){
            buff += FromIntToChar(Carret % default_base);
            Carret /= default_base;
        }

    }


    /// Убрать лидирующие нули
    while(buff.back() == '0' ){
        buff.pop_back();
        if (buff.empty()){
            return (os << "0");
        }
    }



    reverse(buff.begin(),buff.end());

	return (os << buff);
}

int next_power_of_two(int n) {
    int i = 0;
    for (--n; n > 0; n >>= 1) {
        i++;
    }
    return 1 << i;
}

std::istream& operator>>(std::istream& in, BigUnsigned &bi) {


    std::string stream_;
    in >> stream_;

    new (&bi) BigUnsigned(stream_);

    /// мб тут надо регистрировать "лидирующие" нули, но хз

    return in;

}
