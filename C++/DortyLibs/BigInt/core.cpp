

int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}

// ������� ������� ����� ����� �� ��������� 0
BigInt::BigInt() {
	this->_is_negative = false;
}

// ������� ������� ����� ����� �� C++-������
BigInt::BigInt(std::string str) {
	/// to_do
}

// �������� ��� ������� �� 1 ������ (��������� �� BASE)
void BigInt::_shift_right() {

    /// removed exceptions

	_digits.push_back(_digits[_digits.size() - 1]);
	for (size_t i = _digits.size() - 2; i > 0; --i) _digits[i] = _digits[i - 1];
	_digits[0] = 0;
}

// �������� ��� ������� �� 1 ������ (��������� �� BASE)
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

// ������� ������� ����
void BigInt::_remove_leading_zeros() {
	while (this->_digits.size() > 1 && this->_digits.back() == 0) {
		this->_digits.pop_back();
	}

	if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// ����������� ����� � ������
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

// ���������, �������� �� ������� ����� ��������
bool BigInt::odd() const {
	if (this->_digits.size() == 0) return false;
	return this->_digits[0] & 1;
}

// ���������, �������� �� ������� ����� ������
bool BigInt::even() const {
	return !this->odd();
}


/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
/// ������� ��������. ������ ����� ������������
void inline BigInt::_appendZeros(int length){
    std::vector<long long> v1(length);
    std::vector<long long> tmp = _digits;
    _digits.clear();
    std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(_digits));
}

const int BigInt::get_real_size() const{
    return (_digits.size()-1)*container_stack + intlog(default_base,_digits[_digits.size() - 1]) + 1;
}



