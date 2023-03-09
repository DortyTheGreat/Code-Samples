import math

def p(x,n=0):
    if n == 0:
        n = int(x.bit_length() * 0.3)
    if n < 100:
        return str(x)
    n >>= 1
    l = 10**n
    a,b = divmod(x, l)
    upper = p(a,n)
    lower = p(b,n).rjust(n, "0")
    return upper + lower

in_ = int(input())
#print('inputed')
fact_ = math.factorial(in_)
#print('calc')
print(p(fact_))