/*
/// —ложение двух положительных (исключительно контейнеров)
void BigInt::_add(const BigInt& right) {
    size_t extra_size = 1;

    size_t an_sz = right._digits.size();

    if (an_sz > _digits.size()){
        extra_size = an_sz - _digits.size() + 1;
    }

    for(size_t i = 0;i < extra_size; i++){
        _digits.push_back(0);
    }
    /// «аполн€ем контейнер нул€ми, чтобы было место под новые возможные числа(aka разр€ды)

    for(size_t i = 0; i < an_sz;i++){
        _digits[i] += right._digits[i];
        if (_digits[i] >= BASE){
            _digits[i] -= BASE;
            _digits[i+1]++;
        }
    }

    while(_digits[an_sz] >= BASE){
        _digits[an_sz] -= BASE;
        an_sz++;
        _digits[an_sz]++;
    }



    _remove_leading_zeros();
}

/// ќбработка вычитани€ двух положительных чисел (работает, если второе меньше первого)
void BigInt::_subtract(const BigInt &another){

    size_t an_sz = another._digits.size();

    for(size_t i = 0; i < an_sz;i++){
        _digits[i] -= another._digits[i];
        if (_digits[i] < 0){
            _digits[i] += BASE;
            _digits[i+1]--;
        }
    }

    while(_digits[an_sz] < 0){
        _digits[an_sz] += BASE;
        an_sz++;
        _digits[an_sz]--;
    }



    _remove_leading_zeros();
}
*/
void BigUnsigned::operator +=(const BigUnsigned& right) {
    if (right.alloc_size > alloc_size){
        /// точно переполнение
        return;
    }

    if (right.alloc_size < alloc_size){
        if (_digits[alloc_size - 1] == (BASE-1) ){
            /// ћожет произойти переполнение
        }
    }


}

/**

ѕрибавл€ет второе число к основному. ќднако оно об€зано помещатьс€ в него.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        _digits[i] += right._digits[i];
        if (_digits[i] >= BASE){
            _digits[i] -= BASE;
            ++_digits[i + 1];
        }
    }

    /// ’очетс€, то, что ниже сделать дл€ флекса, но так тоже +- ничего
    CONT_TYPE *p = &_digits[right.real_size];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }


    /*
    CONT_TYPE &p = _digits[right.real_size];
    while (p >= BASE){
        p -= BASE;
        (&p)++;
        ++(p);
    }
    */

    /// Ёто тоже следует улучшить
    real_size = max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (_digits[real_size] != 0){
            ++real_size;
        }
    }


}



/*
/// ¬ерный оператор (с учЄтом знаков и прочего)
void BigInt::operator-=(BigInt right){

    ///std::cout << *this << " " << right << " "<<(compare(*this,right)) << std::endl;
    bool comp_ = !(compare(*this,right));
    if ( comp_){
        ///std::cout << "second is hisher" << std::endl;
        swap(right,*this);
        _is_negative = !_is_negative;
    }


    if ( (_is_negative == right._is_negative) ^ (comp_) ) {
        // ќдинаковы по знаку
        _subtract(right);
    }else{
        // –азные по знаку.
        _add(right);
    }

}
*/





// возвращает копию переданного числа
//const BigInt BigInt::operator +() const {
//	return BigInt(*this);
//}
/*
// возвращает переданное число с другим знаком
const BigInt BigInt::operator -() const {
	BigInt copy(*this);
	copy._is_negative = !copy._is_negative;
	return copy;
}
*/


/**

—кладывает и помещает новое число в новое место в пам€ти (веро€тнее всего присваивать его мы захотим через ->)

*/
const BigUnsigned operator +(const BigUnsigned& left, const BigUnsigned& right) {

    if (left.real_size < right.real_size){
        return right+left;
    }



    BigUnsigned ret;
    ret.assign_from_BU(left.real_size+1,left);




    ret._add(right);

	return ret;
}


/*
// префиксный инкремент
const BigInt BigInt::operator++() {
	return (*this += 1);
}

// постфиксный инкремент
const BigInt BigInt::operator ++(int) {
	*this += 1;
	return *this - 1;
}

// префиксный декремент
const BigInt BigInt::operator --() {
	return *this -= 1;
}


// постфиксный декремент
const BigInt BigInt::operator --(int) {
	*this -= 1;
	return *this + 1;
}

*/
/*
// вычитает два числа
const BigInt operator -(BigInt left, const BigInt& right) {
	left -= right;
	return left;
}

*/

