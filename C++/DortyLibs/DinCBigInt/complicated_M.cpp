/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
 /// Алгоритм Школьного Умножения (взято с доков Питона -> см. https://hg.python.org/cpython/file/b514339e41ef/Objects/longobject.c#l2694)
 /// Не работает правильно с нулём
BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b)
{
    static const CONT_TYPE BASE = a.BASE;

    BigUnsigned z;
    const ubi_szt size_a = a.real_size;
    const ubi_szt size_b = b.real_size;
    ubi_szt i;
    z.alloc_with_zeros(size_a + size_b);




    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < size_a; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a.digits[i];
        CONT_TYPE *pz = z.digits + i;
        CONT_TYPE *pb = b.digits;
        CONT_TYPE *pbend = b.digits + size_b;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }


    if (z.digits[z.alloc_size - 1] == 0){
         z.real_size = z.alloc_size - 1;
    }else{
         z.real_size = z.alloc_size;
    }

    return z;
}


/// это для карацубы, не трогать!
/**

А вообще это для перемножение двух чисел одинакойо длинны, но сразу через массивы.

*/
void x_mul(const CONT_TYPE *__restrict a, CONT_TYPE *__restrict b, CONT_TYPE *__restrict res,const ubi_szt n)
{

    ubi_szt i;




    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < n; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a[i];
        CONT_TYPE *pz = res + i;
        CONT_TYPE *pb = b;
        CONT_TYPE *pbend = b + n;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }



}

#define KAR_TRESH 20



/**

Годная Карацуба.
Требует: 2 "блока" памяти равной длины, (длину блока соответсвенно тоже требует), и место в памяти, куда
поместить результат умножения (место должо быть заранее выделено и заполнено нулями)

(вообще он в третий контейнер как бы добавляет числа, так что если надо добавлять то милости прошу, эта Карацуба это по факту и делает)

TO-DO:

1) Сжатие памяти в одну переменную (вместо двух)
2) ...
3) Починить "растущие" размеры
4) починить долгий минус


*/

void mult(const CONT_TYPE * a, CONT_TYPE * b, CONT_TYPE *__restrict res, const ubi_szt n) {

    /// Слишком маленькое число, запускаем школьный алгоритм
    if (n <= KAR_TRESH) {
        x_mul(a,b,res,n);
    } else {

        const ubi_szt fh = (n+1) / 2;   // First half Data (take more)
        const ubi_szt sh = (n - fh); // Second half of Data

        CONT_TYPE* first = new CONT_TYPE[fh + 1];
        first[fh] = 0;

        CONT_TYPE* second = new CONT_TYPE[fh + 1]; second[fh] = 0;



        memcpy(first,a,fh * sizeof(CONT_TYPE));
        memcpy(second,b,fh * sizeof(CONT_TYPE));



        /// Сто проц можно ускорить сложение
        for (ubi_szt i = 0; i < sh; i++) {
            first[i] += a[i + fh];

            if (first[i] >= BASE){
                first[i] -= BASE;
                ++first[i+1];
            }

            second[i] += b[i + fh];
            if (second[i] >= BASE){
                second[i] -= BASE;
                ++second[i+1];
            }
        }
        /// Доп. чек на переволнение последнего контейнера
        if (first[fh - 1] >= BASE){
                first[fh - 1] -= BASE;
                ++first[fh];
            }
        if (second[fh - 1] >= BASE){
            second[fh - 1] -= BASE;
            ++second[fh];
        }


        /// first += a offseted by fh
        /// second += b offseted by sh


        //mult(first, second, res + fh, fh + 1);
        //delete first;
        //delete second;

        mult(a + 0, b + 0, res, fh);
        mult(a + fh, b + fh, res + fh*2, sh);
        CONT_TYPE * we_need_to_optimize_memory = new CONT_TYPE[2* (fh + 1)]{0};


        mult(first, second, we_need_to_optimize_memory, fh + 1);

        for(ubi_szt i = 0; i < 2 * sh; ++i){

            we_need_to_optimize_memory[i] -= (res[i] + res[2 * fh + i]);

        }

        if (sh != fh){

            we_need_to_optimize_memory[2 * sh] -= res[2 * sh];
            we_need_to_optimize_memory[2 * sh + 1] -= res[2 * sh + 1];
        }

        /// Это тоже ужасное вычитание !!
        for(ubi_szt i = 0; i < 2 * fh + 2;++i){

            res[fh + i] += we_need_to_optimize_memory[i];
            if (res[fh + i]  >= BASE){
                res[fh + i] -= BASE;
                ++res[fh + 1 + i];
            }else{
                while (res[fh + i]  < 0){
                    res[fh + i] += BASE;
                    --res[fh + 1 + i];
                }
            }
        }







        /// Не забыть не только отпимизирвать память, но и размеры



    }


}



/// Пока Карацуба Думает, что у чисел одинаковый размер

/// Не до конца доделано, размер real_size обкуренный -> при умножении на нуль делает Пиво
/// Ещё изменяет размер в добавок
BigUnsigned karatsuba(BigUnsigned& left, BigUnsigned& right){
    /// Если правый больше -> тогда результат будет меньше требуемого
    if (left.alloc_size < right.real_size){
        CONT_TYPE *remem = left.digits;
        left.alloc_with_zeros(right.real_size);

        memcpy(left.digits, remem, left.real_size * sizeof(CONT_TYPE));
    }


    /// Если левый больше -> входим в неаллокейтед память
    if (right.alloc_size < left.real_size){
        //cout << right << endl;
        CONT_TYPE *remem = right.digits;
        right.alloc_with_zeros(left.real_size);

        memcpy(right.digits, remem, right.real_size * sizeof(CONT_TYPE));
        //cout << right << endl;
    }





    BigUnsigned res;
    res.alloc_with_zeros(2 * std::max(left.real_size,right.real_size));
    mult(left.digits,right.digits,res.digits,std::max(left.real_size,right.real_size));



    if (res.digits[res.alloc_size - 1] == 0){
         res.real_size = res.alloc_size - 1;
    }else{
         res.real_size = res.alloc_size;
    }



    return res;

}




