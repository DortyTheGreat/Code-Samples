/// Обработка сравнения двух положительных чисел (0 => второе больше, 1 => равны, 2 => наше больше)
short inline compare(const BigInt &left, const BigInt &right){
    size_t sz = left._digits.size();
    if (right._digits.size() != sz){
        return (sz > right._digits.size()) << 1;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] > right._digits[p]) << 1;
        }
    }

    return 1;
}




// проверяет, является ли левый операнд меньше правого
bool operator <(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return left._is_negative;
    }

	if (left._digits.size() != right._digits.size()){
        return (left._digits.size() < right._digits.size()) ^ (left._is_negative);
    }

    int sz = left._digits.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] < right._digits[p]) ^ (left._is_negative);
        }
    }

    // Числа равны
    return 0;
}

// проверяет, является ли левый операнд меньше правого
bool operator ==(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return 0;
    }

	if (left._digits.size() != right._digits.size()){
        return 0;
    }

    int sz = left._digits.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return 0;
        }
    }

    // Числа равны
    return 1;
}

// сравнивает два числа на неравенство
bool operator !=(const BigInt& left, const BigInt& right) {
	return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const BigInt& left, const BigInt& right) {
	return !(right < left);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const BigInt& left, const BigInt& right) {
	return (right < left);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const BigInt& left, const BigInt& right) {
	return !(left < right);
}

