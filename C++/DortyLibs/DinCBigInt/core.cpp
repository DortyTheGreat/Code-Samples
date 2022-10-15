
BigUnsigned::~BigUnsigned(){
    delete [] digits;
}

BigUnsigned::BigUnsigned()
: digits( new CONT_TYPE[1])
, real_size(1)
, alloc_size(1)
{digits[0] = 0;}

BigUnsigned::BigUnsigned (BigUnsigned&& bu)
: digits( bu.digits  )
, real_size( bu.real_size )
, alloc_size( bu.alloc_size )
{bu.digits = NULL;}

BigUnsigned::BigUnsigned(const BigUnsigned& bu) : real_size(bu.real_size)
{
    ///cout << "called copy constructor" << endl;
    if (bu.real_size > alloc_size){
        alloc_size = bu.alloc_size;
        digits = new CONT_TYPE[alloc_size];
        ///digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ИЛИ new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;

    memcpy(digits,bu.digits,sizeof(CONT_TYPE) * bu.alloc_size);

}

BigUnsigned& BigUnsigned::operator= (BigUnsigned&& bu)
{
    //cout << "called move equality" << endl;
    digits = ( bu.digits  );
    real_size = ( bu.real_size );
    alloc_size = ( bu.alloc_size );


    bu.digits = NULL;
    return *this;
}

BigUnsigned& BigUnsigned::operator= (const BigUnsigned& bu){
    ///cout << "called copy equality" << endl;
    if (bu.real_size > alloc_size){
        alloc_size = bu.alloc_size;
        digits = new CONT_TYPE[alloc_size];


        ///digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ИЛИ new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;

    memcpy(digits,bu.digits,sizeof(CONT_TYPE) * bu.alloc_size);

    return *this;
}

void BigUnsigned::alloc_with_zeros(const int sz){
    alloc_size = sz;
    digits = new CONT_TYPE[sz]{0};

}

void BigUnsigned::alloc(const int sz){
    alloc_size = sz;
    digits = new CONT_TYPE[sz];
}

void BigUnsigned::resize(const int sz){
    alloc_size = sz;
    digits = new CONT_TYPE[sz];
    real_size = sz;
}

/**

Тоже самое, что и оператор=, но можно указать количество памяти для аллокации

ПЕРЕПИСАТЬ НА МЕМ_СЕТ http://cppstudio.com/post/673/

*/
void BigUnsigned::assign_from_BU(const int alloc_space, const BigUnsigned& bu){
    alloc_with_zeros(alloc_space);
    real_size = bu.real_size;
    memcpy(digits,bu.digits,real_size * sizeof(CONT_TYPE));
}


/**
    Системная функция. Требуется для тех случаев, когда real_size выше чем "реальный" размер.
    (просто уменьшает real_size)
*/
void BigUnsigned::_remove_leading_zeros(){
    int cur = real_size - 1;
    for( ; cur != 0 ; --cur){
        if (digits[cur] != 0){
            break;
        }
    }
    real_size = cur + 1;
}



BigUnsigned::BigUnsigned (const std::string& stream_){
    ubi_szt carret_r_sz = stream_.size();
    real_size = (carret_r_sz+cnt_stack-1)/cnt_stack;
    alloc_with_zeros(next_power_of_two(real_size));

    CONT_TYPE Carret;

    for(ubi_szt i = 0;i<real_size;++i){
        Carret = 0;
        for(ubi_szt j = 0; j < cnt_stack;++j){
            int index = carret_r_sz - (i+1)*cnt_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        digits[i] = Carret;
    }
}







