
/// Обработка сравнения двух положительных чисел (0 => второе больше, 1 => равны, 2 => наше больше)
short inline compare(const BigUnsigned &left, const BigUnsigned &right){
    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size > right.real_size) << 1;
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
bool operator <(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size < right.real_size);
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] < right._digits[p]);
        }
    }

    return 0;
}

// проверяет, является ли левый операнд меньше правого
bool operator ==(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return 0;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return 0;
        }
    }

    return 1;
}

// сравнивает два числа на неравенство
bool operator !=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(right < left);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const BigUnsigned& left, const BigUnsigned& right) {
	return (right < left);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left < right);
}

