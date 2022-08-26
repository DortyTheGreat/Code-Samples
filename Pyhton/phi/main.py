# primefac.factorint(n) returns a factor:multiplicity dict
from sympy import factorint

def totient(n):
    totient = n
    print(factorint(n))
    for factor in factorint(n):
        print(factor)
        totient -= totient // factor
    return totient

print(totient(10000))