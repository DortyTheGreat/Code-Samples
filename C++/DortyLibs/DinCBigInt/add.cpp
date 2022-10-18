/*
void BigUnsigned::operator +=(const BigUnsigned& right) {
    if (right.alloc_size > alloc_size){
        /// точно переполнение
        return;
    }

    if (right.alloc_size < alloc_size){
        if (digits[alloc_size - 1] == (BASE-1) ){
            /// Может произойти переполнение
        }
    }


}
*/

/**

Способно отработать нормально, если ...

+ НЕ ЗАБУДЬ ПРО real_size

*/
void BigUnsigned::operator -=(const BigUnsigned& minus) {

    for(int i = 0;i< minus.real_size; ++i){
        digits[i] -= minus.digits[i];
        if (digits[i] < 0){
            digits[i] += BASE;
            --digits[i+1];
        }
    }

    if (minus.real_size != real_size){



        /// Замечу что первый проход не имеет смысла :-)
        for(int j = minus.real_size; digits[j] < 0;++j){

            digits[j] += BASE;
            --digits[j+1];

        }
    }

    _remove_leading_zeros();




}

/**

Прибавляет второе число к основному. Однако результат обязан помещаться в изначальное.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        digits[i] += right.digits[i];
        incrSanitise(i);
    }

    incrSanitises(right.real_size)





    /// Это тоже следует улучшить
    real_size = std::max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (digits[real_size] != 0){
            ++real_size;
        }
    }


}






const BigUnsigned operator +(const BigUnsigned& left, const BigUnsigned& right) {
    if (left.real_size < right.real_size){
        return right+left;
    }


    BigUnsigned ret;
    ret.assign_from_BU(left.real_size+1,left);
    ret._add(right);

	return ret;
}





// префиксный инкремент
void BigUnsigned::operator++() {

	++digits[0];
	for ( ubi_szt cou = 0; cou < real_size -1; ++cou){
        if (digits[cou] < BASE){ return;}

        digits[cou] -= BASE; /// можно записать = 0 в целом, если изначальное число сбалансировано
        ++digits[cou+1];
	}

    if (digits[real_size - 1] >= BASE ){
        if (real_size == alloc_size){
            /// reallocate memory
            CONT_TYPE * new_c = new CONT_TYPE[++alloc_size];
            memcpy(new_c, digits, real_size * sizeof(CONT_TYPE));
            new_c[real_size] = 0;
            digits = new_c;
        }

        digits[real_size - 1] -= BASE;
        ++digits[real_size++];

    }
}

void BigUnsigned::operator--() {

	--digits[0];



    for(int j = 0; digits[j] < 0;++j){

        digits[j] += BASE;
        --digits[j+1];

    }


    _remove_leading_zeros();
}


