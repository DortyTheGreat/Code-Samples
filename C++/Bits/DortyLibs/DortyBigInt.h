
char FromIntToChar(int a){
switch(a){
case 0: return '0';
case 1: return '1';
case 2: return '2';
case 3: return '3';
case 4: return '4';
case 5: return '5';
case 6: return '6';
case 7: return '7';
case 8: return '8';
case 9: return '9';
case 10: return 'A';
case 11: return 'B';
case 12: return 'C';
case 13: return 'D';
case 14: return 'E';
case 15: return 'F';
case 16: return 'G';
case 17: return 'H';
case 18: return 'I';
case 19: return 'J';
case 20: return 'K';
case 21: return 'L';
case 22: return 'M';
case 23: return 'N';
case 24: return 'O';
case 25: return 'P';
case 26: return 'Q';
case 27: return 'R';
case 28: return 'S';
case 29: return 'T';
case 30: return 'U';
case 31: return 'V';
case 32: return 'W';
case 33: return 'X';
case 34: return 'Y';
case 35: return 'Z';
}
}

int FromCharToInt(char a){
if(a == '0'){return 0;}
if(a == '1'){return 1;}
if(a == '2'){return 2;}
if(a == '3'){return 3;}
if(a == '4'){return 4;}
if(a == '5'){return 5;}
if(a == '6'){return 6;}
if(a == '7'){return 7;}
if(a == '8'){return 8;}
if(a == '9'){return 9;}
if(a == 'A'){return 10;}
if(a == 'B'){return 11;}
if(a == 'C'){return 12;}
if(a == 'D'){return 13;}
if(a == 'E'){return 14;}
if(a == 'F'){return 15;}
if(a == 'G'){return 16;}
if(a == 'H'){return 17;}
if(a == 'I'){return 18;}
if(a == 'J'){return 19;}
if(a == 'K'){return 20;}
if(a == 'L'){return 21;}
if(a == 'M'){return 22;}
if(a == 'N'){return 23;}
if(a == 'O'){return 24;}
if(a == 'P'){return 25;}
if(a == 'Q'){return 26;}
if(a == 'R'){return 27;}
if(a == 'S'){return 28;}
if(a == 'T'){return 29;}
if(a == 'U'){return 30;}
if(a == 'V'){return 31;}
if(a == 'W'){return 32;}
if(a == 'X'){return 33;}
if(a == 'Y'){return 34;}
if(a == 'Z'){return 35;}

}


/// ���������� ������ ������� �����, ����� ������ ������������ �����.
class BigInt{
private:
    void _remove_leading_zeros();
    bool _is_negative = false;



public:
    /// 1234 === [4,3,2,1]
    vector<int> data;
    int Base = 10;

    const int zero = 0;

    BigInt(){data = {0};}

    BigInt(long long num, int Base_){
        while(num != 0){
            data.push_back(num % Base_);
            num /= Base;
        }

        if (data.size() == 0){

        }
    }

    istream& input(int  Base_,istream& in){
        Base = Base_;
        string stream_;
        in >> stream_;

        int sz = stream_.size();

        data.resize(sz);

        for(int i = 0;i<sz;i++){
            data[sz - i - 1] = FromCharToInt(stream_[i]);
        }

        _remove_leading_zeros();

        return in;


    }

    /// ��������� ��������� ���� ������������� ����� (0 => ������ ������, 1 => �����, 2 => ���� ������)
    short compare(BigInt &another){
        if (another.data.size() != data.size()){
            return (data.size() > another.data.size()) << 1;
        }

        int sz = data.size();

        for (int i = 0;i<sz;i++){
            int p = sz - i - 1;
            if (data[p] != another.data[p]){
                return (data[p] > another.data[p]) << 1;
            }
        }

        return 1;
    }

    /// ��������� �������� ���� ������������� �����
    void operator+=(BigInt &another){

        size_t extra_size = 1;

        size_t an_sz = another.data.size();

        if (an_sz > data.size()){
            extra_size = an_sz - data.size() + 1;
        }

        for(int i = 0;i < extra_size; i++){
            data.push_back(zero);
        }
        /// ��������� ��������� ������, ����� ���� ����� ��� ����� ��������� �����(aka �������)

        for(size_t i = 0; i < an_sz;i++){
            data[i] += another.data[i];
            if (data[i] >= Base){
                data[i] -= Base;
                data[i+1]++;
            }
        }

        while(data[an_sz] >= Base){
            data[an_sz] -= Base;
            an_sz++;
            data[an_sz]++;
        }



        _remove_leading_zeros();
    }


    /// ��������� ��������� ���� ������������� ����� (��������, ���� ������ ������ �������)
    void operator-=(BigInt &another){

        size_t an_sz = another.data.size();

        for(size_t i = 0; i < an_sz;i++){
            data[i] -= another.data[i];
            if (data[i] < zero){
                data[i] += Base;
                data[i+1]--;
            }
        }

        while(data[an_sz] < 0){
            data[an_sz] += Base;
            an_sz++;
            data[an_sz]--;
        }



        _remove_leading_zeros();
    }

    friend istream& operator>>(istream& in, BigInt &bi) {
        return bi.input(10,in);

    }

    friend ostream& operator<<(ostream &in, const BigInt &bi) {

        int sz = bi.data.size();

        for(int i = 0;i<sz;i++){
            in << FromIntToChar(bi.data[sz - i - 1]);
        }

        return in;
    }

    /*
    void Stabilize(){
        for(int i=SIZEE_-1;i>-1;i--){
            OneNumTransform(i);
        }
    }
    */

public:

};





void BigInt::_remove_leading_zeros() {
	while (this->data.size() > 1 && this->data.back() == 0) {
		this->data.pop_back();
	}

	if (this->data.size() == 1 && this->data[0] == 0) this->_is_negative = false;
}
