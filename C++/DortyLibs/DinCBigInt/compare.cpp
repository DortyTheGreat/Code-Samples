
/// ��������� ��������� ���� ������������� ����� (0 => ������ ������, 1 => �����, 2 => ���� ������)
short inline compare(const BigUnsigned &left, const BigUnsigned &right){
    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size > right.real_size) << 1;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.digits[p] != right.digits[p]){
            return (left.digits[p] > right.digits[p]) << 1;
        }
    }

    return 1;
}




// ���������, �������� �� ����� ������� ������ �������
bool operator <(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size < right.real_size);
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.digits[p] != right.digits[p]){
            return (left.digits[p] < right.digits[p]);
        }
    }

    return 0;
}

// ���������, �������� �� ����� ������� ������ �������
bool operator ==(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return 0;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.digits[p] != right.digits[p]){
            return 0;
        }
    }

    return 1;
}

bool operator !=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left == right);
}

bool operator <=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(right < left);
}

bool operator >(const BigUnsigned& left, const BigUnsigned& right) {
	return (right < left);
}

bool operator >=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left < right);
}

