num_10_16 = 10000000000000000
num_10_6 = 1000000

import sympy

mod = 993353399

BIG_BOY = 0

def f(n):

    vc = sympy.divisors(n)

    summ = 0
    for elem in vc:
        vc2 = sympy.divisors(elem)

        summ_inside = 0

        for elem2 in vc2:
            summ_inside += (elem2 % mod) * (sympy.totient(n // elem2) % mod)
            summ_inside %= mod




        summ_inside *= summ_inside
        summ_inside %= mod

        summ += summ_inside * (sympy.totient(n // elem) % mod)
        summ %= mod


    n %= mod

    summ += n * n
    summ %= mod

    return summ


for i in range(num_10_6 + 1):
    j = num_10_16 + i
    if sympy.isprime(j):
        print(j)
        BIG_BOY += f(j-1)
        BIG_BOY %= mod



print(BIG_BOY);