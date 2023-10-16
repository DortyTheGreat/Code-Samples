import pandas as pd
import numpy as np


from sympy import *

m1 = 1 # минимальное значение производной на отрезке

sp_i = []
sp_x = []
sp_f = []

def f(x):
    return sin(1 - 0.2*x*x) - x

def f_prime(x):
    return -1 - 0.4*x*cos(1 - 0.2*x*x)

def newton_method(f, f_prime, x0, max_iterations=4):
    x = x0
    for i in range(max_iterations):
        sp_i.append(i)
        sp_x.append(x)
        sp_f.append(f(x))
        fx = f(x)
        fpx = f_prime(x)
        if fpx == 0:
            break
        x = x - fx / fpx
    return x



root = newton_method(f, f_prime, x0=2)

df = pd.DataFrame(data={'n':range(sp_i[-1]+1), 'x': sp_x, 'f(x)': sp_f})
print(df)

