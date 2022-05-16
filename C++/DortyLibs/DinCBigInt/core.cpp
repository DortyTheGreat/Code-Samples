/**

Оператор полного присваивания (копирования). Дольше, чем ->

Придётся ещё ебаться с нулями, которые могут лежать в памяти(точнее как раз не лежать в памяти)

Есть 2 варианта

1) Всё-таки заполнять нулями
2) Ебаться отдельно во всех других функциях.

*/
void BigUnsigned::operator =(const BigUnsigned& bu){
    cout << "started equality" << endl;
    if (bu.real_size > alloc_size){
        alloc_size = bu.alloc_size;
        _digits = new CONT_TYPE[alloc_size];


        ///_digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ИЛИ new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;

    memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * bu.alloc_size);
}

/*
void BigUnsigned::operator =(BigUnsigned&& bu){
    real_size = bu.real_size;
    alloc_size = bu.alloc_size;
    _digits = bu._digits;
}
*/

void BigUnsigned::alloc_with_zeros(const int sz){
    alloc_size = sz;
    _digits = new CONT_TYPE[sz]{0};

}

/**

Тоже самое, что и оператор=, но можно указать количество памяти для аллокации

ПЕРЕПИСАТЬ НА МЕМ_СЕТ http://cppstudio.com/post/673/

*/
void BigUnsigned::assign_from_BU(const int alloc_space, const BigUnsigned& bu){
    alloc_with_zeros(alloc_space);
    real_size = bu.real_size;
    memcpy(_digits,bu._digits,real_size * sizeof(CONT_TYPE));
}


/**
    Системная функция. Требуется для тех случаев, когда real_size выше чем "реальный" размер.
    (просто уменьшает real_size)
*/
void BigUnsigned::_remove_leading_zeros(){
    int cur = real_size - 1;
    for( ; cur != 0 ; --cur){
        if (_digits[cur] != 0){
            break;
        }
    }
    real_size = cur + 1;
}

/*
int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}

// создает длинное целое число со значением 0
BigInt::BigInt() {
	this->_is_negative = false;
}

// создает длинное целое число из C++-строки
BigInt::BigInt(std::string str) {
	/// to_do
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInt::_shift_right() {

    /// removed exceptions

	_digits.push_back(_digits[_digits.size() - 1]);
	for (size_t i = _digits.size() - 2; i > 0; --i) _digits[i] = _digits[i - 1];
	_digits[0] = 0;
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInt::_double_shift_right() {

    /// removed exceptions

    if (_digits.size() == 1){
        _digits = {0,0,_digits[0]};
        return;
    }

	_digits.push_back(_digits[_digits.size() - 2]);
	_digits.push_back(_digits[_digits.size() - 2]);
	for (size_t i = _digits.size() - 3; i > 1; --i) _digits[i] = _digits[i - 2];
	_digits[0] = 0;
	_digits[1] = 0;
}

// удаляет ведущие нули
void BigInt::_remove_leading_zeros() {
	while (this->_digits.size() > 1 && this->_digits.back() == 0) {
		this->_digits.pop_back();
	}

	if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// преобразует число к строке
BigInt::operator std::string() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

BigInt::BigInt(long long num){
    _is_negative = (num < 0);
    num = abs(num);
    while(num != 0){
        _digits.push_back(num % BASE);
        num /= BASE;
    }

    if (_digits.size() == 0){
        _digits.push_back(0);
    }
}


BigInt::BigInt(int num){
    _is_negative = (num < 0);
    num = abs(num);
    while(num != 0){
        _digits.push_back(num % BASE);
        num /= BASE;
    }

    if (_digits.size() == 0){
        _digits.push_back(0);
    }
}

// проверяет, является ли текущее число нечетным
bool BigInt::odd() const {
	if (this->_digits.size() == 0) return false;
	return this->_digits[0] & 1;
}

// проверяет, является ли текущее число четным
bool BigInt::even() const {
	return !this->odd();
}


/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
/// Следует Улучшить. Ужасно плохо реализованно
void inline BigInt::_appendZeros(int length){
    std::vector<CONT_TYPE> v1(length);
    std::vector<CONT_TYPE> tmp = _digits;
    _digits.clear();
    std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(_digits));
}

const int BigInt::get_real_size() const{
    return (_digits.size()-1)*container_stack + intlog(default_base,_digits[_digits.size() - 1]) + 1;
}
*/



