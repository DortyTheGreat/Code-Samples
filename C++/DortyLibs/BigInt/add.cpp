
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

void BigInt::operator +=(const BigInt& right) {
    if (_is_negative == right._is_negative){
        _add(right);
    }else{
        /// ������� ����������������
        _is_negative = !_is_negative;
        *this -= right;
        _is_negative = !_is_negative;
    }
}




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
// ���������� ��� �����
const BigInt operator +(BigInt left, const BigInt& right) {
	left += right;
	return left;
}

/*
// ���������� ���������
const BigInt BigInt::operator++() {
	return (*this += 1);
}

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

// �������� ��� �����
const BigInt operator -(BigInt left, const BigInt& right) {
	left -= right;
	return left;
}



