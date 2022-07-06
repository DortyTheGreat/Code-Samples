/*
/// �������� ���� ������������� (������������� �����������)
void BigInt::_add(const BigInt& right) {
    size_t extra_size = 1;

    size_t an_sz = right._digits.size();

    if (an_sz > _digits.size()){
        extra_size = an_sz - _digits.size() + 1;
    }

    for(size_t i = 0;i < extra_size; i++){
        _digits.push_back(0);
    }
    /// ��������� ��������� ������, ����� ���� ����� ��� ����� ��������� �����(aka �������)

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

/// ��������� ��������� ���� ������������� ����� (��������, ���� ������ ������ �������)
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
        /// ����� ������������
        return;
    }

    if (right.alloc_size < alloc_size){
        if (_digits[alloc_size - 1] == (BASE-1) ){
            /// ����� ��������� ������������
        }
    }


}
/**

�������� ���������� ���������, ���� ...

+ �� ������ ��� real_size

*/
void BigUnsigned::operator -=(const BigUnsigned& minus) {

    for(int i = 0;i< minus.real_size; ++i){
        _digits[i] -= minus._digits[i];
        if (_digits[i] < 0){
            _digits[i] += BASE;
            --_digits[i+1];
        }
    }

    if (minus.real_size != real_size){



        /// ������ ��� ������ ������ �� ����� ������ :-)
        for(int j = minus.real_size; _digits[j] < 0;++j){

            _digits[j] += BASE;
            --_digits[j+1];

        }
    }

    _remove_leading_zeros();




}

/**

���������� ������ ����� � ���������. ������ ��� ������� ���������� � ����.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        _digits[i] += right._digits[i];
        if (_digits[i] >= BASE){
            _digits[i] -= BASE;
            ++_digits[i + 1];
        }
    }

    /// �������, ��, ��� ���� ������� ��� ������, �� ��� ���� +- ������
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

    /// ��� ���� ������� ��������
    real_size = max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (_digits[real_size] != 0){
            ++real_size;
        }
    }


}



/*
/// ������ �������� (� ������ ������ � �������)
void BigInt::operator-=(BigInt right){

    ///std::cout << *this << " " << right << " "<<(compare(*this,right)) << std::endl;
    bool comp_ = !(compare(*this,right));
    if ( comp_){
        ///std::cout << "second is hisher" << std::endl;
        swap(right,*this);
        _is_negative = !_is_negative;
    }


    if ( (_is_negative == right._is_negative) ^ (comp_) ) {
        // ��������� �� �����
        _subtract(right);
    }else{
        // ������ �� �����.
        _add(right);
    }

}
*/





// ���������� ����� ����������� �����
//const BigInt BigInt::operator +() const {
//	return BigInt(*this);
//}
/*
// ���������� ���������� ����� � ������ ������
const BigInt BigInt::operator -() const {
	BigInt copy(*this);
	copy._is_negative = !copy._is_negative;
	return copy;
}
*/


/**

���������� � �������� ����� ����� � ����� ����� � ������ (��������� ����� ����������� ��� �� ������� ����� ->)

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


const BigUnsigned operator +(BigUnsigned&& left, const BigUnsigned& right) {
    cout << "called rvalue" << endl;
    if (left.real_size < right.real_size){
        //return right+left;
    }

    left += right;

	return left;
}



// ���������� ���������
void BigUnsigned::operator++() {

	++_digits[0];
	for ( ubi_szt cou = 0; cou < real_size -1; ++cou){
        if (_digits[cou] < BASE){ return;}

        _digits[cou] -= BASE; /// ����� �������� = 0 � �����, ���� ����������� ����� ��������������
        ++_digits[cou+1];
	}

    if (_digits[real_size - 1] >= BASE ){
        if (real_size == alloc_size){
            /// reallocate memory
            CONT_TYPE * new_c = new CONT_TYPE[++alloc_size];
            memcpy(new_c, _digits, real_size * sizeof(CONT_TYPE));
            new_c[real_size] = 0;
            _digits = new_c;
        }

        _digits[real_size - 1] -= BASE;
        ++_digits[real_size++];

    }
}
/*
// ����������� ���������
const BigInt BigInt::operator ++(int) {
	*this += 1;
	return *this - 1;
}

// ���������� ���������
const BigInt BigInt::operator --() {
	return *this -= 1;
}


// ����������� ���������
const BigInt BigInt::operator --(int) {
	*this -= 1;
	return *this + 1;
}

*/
/*
// �������� ��� �����
const BigInt operator -(BigInt left, const BigInt& right) {
	left -= right;
	return left;
}

*/

