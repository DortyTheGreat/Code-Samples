from math import floor, log10

def firstDigDumb(n):
    return int ((str)(2**n) [0])

def firstDigSmart(n):
    if (n == 3): return 8 # not so random corner case
    return floor(10**(n * log10(2) - floor(n * log10(2))))


for i in range(50000):
    if (firstDigSmart(i) != firstDigDumb(i)):
        print(i, firstDigSmart(i), firstDigDumb(i))

