#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define FORCE_INLINE __attribute__( ( always_inline ) ) static inline
/// #define FORCE_INLINE __attribute__((always_inline)) inline
FORCE_INLINE char FromIntToChar(const int& a){
    if (a >= 0 && a <= 9){
        return (a + '0');
    }
    return (a - 10) + 'A';
}

FORCE_INLINE int FromCharToInt(const char& a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }
    return (a - 'A')+10;
}

int cnt_stack = 1;
int default_base = 10;
int BASE = 10;
struct BigUnsigned : vector<int>{
    BigUnsigned (const std::string& str="0");
    //BigUnsigned () = default;
    //~BigUnsigned() = default;
    explicit operator std::string() const;
    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);


	BigUnsigned& operator*=(int mult){
	    push_back(0);
	    int64_t value;
        for(int i = size() - 2; i > -1; --i){
            value = ((int64_t)((*this)[i])) * mult;
            int64_t divis = value / BASE;
            if ( ((*this)[i+1] += divis) >= BASE ){
                (*this)[i+1] -= BASE;
                ++((*this)[i+2]);
            }
            (*this)[i] = value - divis*BASE;
        }

        if ((*this)[size() - 1] == 0)
            pop_back();
        return *this;
	}


	void operator++() {

        ++((*this)[0]);
        for ( size_t cou = 0; cou < size() -1; ++cou){
            if (((*this)[cou]) < BASE){ return;}

            ((*this)[cou]) -= BASE; /// ЋЌ‘ћЌ √ёќ’яё–Ё = 0 Ѕ ∆≈ ЌЋ, ≈я ’ ’√ћё¬ё ЁћЌ≈ ¬’я Ќ яјё ёћя’ѕЌЅёћЌ
            ++((*this)[cou+1]);
        }

        if (((*this)[size() - 1]) >= BASE ){
            ((*this)[size() - 1]) -= BASE;
            push_back(1);
        }
    }
};


#include <algorithm> /// дл€ реверса string



BigUnsigned::operator std::string() const{
    /*
	if ( (bi.digits.size() == 1) && (bi.digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }
    */




    int Carret;
    std::string buff = "";
    for(size_t i = 0;i<size();++i){
        Carret = (*this)[i];
        for(int j = 0; j < cnt_stack;++j){
            buff += FromIntToChar(Carret % default_base);
            Carret /= default_base;
        }

    }


    /// ”брать лидирующие нули
    while(buff.back() == '0' ){
        buff.pop_back();
        if (buff.empty()){
            return "0";
        }
    }



    reverse(buff.begin(),buff.end());

	return buff;
}

// печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const BigUnsigned& bi) {
    return os << std::string(bi);
}


std::istream& operator>>(std::istream& in, BigUnsigned &bi) {


    std::string stream_;
    in >> stream_;

    new (&bi) BigUnsigned(stream_);

    /// мб тут надо регистрировать "лидирующие" нули, но хз

    return in;

}


BigUnsigned::BigUnsigned (const std::string& stream_){
    size_t carret_r_sz = stream_.size();
    resize((carret_r_sz+cnt_stack-1)/cnt_stack);


    int Carret;

    for(size_t i = 0;i<size();++i){
        Carret = 0;
        for(size_t j = 0; j < cnt_stack;++j){
            int index = carret_r_sz - (i+1)*cnt_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        (*this)[i] = Carret;
    }
}




int main()
{


    for(int ss = 3; ss < 50; ++ss){


        cnt_stack = 1;
        default_base = ss;
        BASE = ss;

        BigUnsigned bi = string("1");
        BigUnsigned bi2 = string("1");
        for(int itter = 0; itter < 1000 * 1000; ++itter){
            bi2 = bi;
            bi2 *= 2;



            map<int,int> mp1;
            map<int,int> mp2;
            for(const int& it : bi){
                mp1[ it ]++;
            }

            for(const int& it : bi2){
                mp2[it ]++;
            }


            bool flag = true;
            for(const auto& p : mp1){
                if (p.first == 0) continue;
                if (mp2[p.first] != p.second){
                    flag = false;
                    break;
                }
            }


            for(const auto& p : mp2){
                if (p.first == 0) continue;
                if (mp1[p.first] != p.second){
                    flag = false;
                    break;
                }
            }



            if (flag){
                ///cout << ss <<" : " << bi<< " " << bi2 << endl;
                cout << ss << " : ";
                for(const int& it : bi){
                    cout << it << " ";
                }
                cout << endl;

                break;
            }

            ++bi;
        }

    }


    return 0;
}
