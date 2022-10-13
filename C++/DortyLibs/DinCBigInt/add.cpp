

template <typename T>
inline void BigUnsigned::PositiveSanitise(const T& index){
    for ( ubi_szt cou = index; cou < real_size -1; ++cou){
        if (digits[cou] < BASE){ return;}

        digits[cou] -= BASE; /// ����� �������� = 0 � �����, ���� ����������� ����� ��������������
        ++digits[cou+1];
	}

    if (digits[real_size - 1] >= BASE ){
        if (real_size == alloc_size){
            /// reallocate memory
            CONT_TYPE * new_c = new CONT_TYPE[++alloc_size];
            memcpy(new_c, digits, real_size * sizeof(CONT_TYPE));
            delete [] digits;
            digits = new_c;
        }

        digits[real_size - 1] -= BASE;
        digits[real_size++] = 1;

    }
}

void BigUnsigned::operator +=(const BigUnsigned& right) {
    if (right.alloc_size > alloc_size){
        /// ����� ������������
        return;
    }

    if (right.alloc_size < alloc_size){
        if (digits[alloc_size - 1] == (BASE-1) ){
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
        digits[i] -= minus.digits[i];
        if (digits[i] < 0){
            digits[i] += BASE;
            --digits[i+1];
        }
    }

    if (minus.real_size != real_size){



        /// ������ ��� ������ ������ �� ����� ������ :-)
        for(int j = minus.real_size; digits[j] < 0;++j){

            digits[j] += BASE;
            --digits[j+1];

        }
    }

    _remove_leading_zeros();




}

/**

���������� ������ ����� � ���������. ������ ��� ������� ���������� � ����.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        digits[i] += right.digits[i];
        if (digits[i] >= BASE){
            digits[i] -= BASE;
            ++digits[i + 1];
        }
    }


    CONT_TYPE *p = &digits[right.real_size];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }




    /// ��� ���� ������� ��������
    real_size = std::max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (digits[real_size] != 0){
            ++real_size;
        }
    }


}

const BigUnsigned operator +(const BigUnsigned& left, const BigUnsigned& right) {
    BigUnsigned ret;
    if (left.real_size < right.real_size){
        ret.assign_from_BU(right.real_size+1,right);
        ret._add(left);
        return ret;
    }
    ret.assign_from_BU(left.real_size+1,left);
    ret._add(right);
    return ret;
}






// ���������� ���������
void BigUnsigned::operator++() {

	++digits[0];

}

void BigUnsigned::operator--() {

	--digits[0];



    for(int j = 0; digits[j] < 0;++j){

        digits[j] += BASE;
        --digits[j+1];

    }


    _remove_leading_zeros();
}


