import pandas as pd
import numpy as np


from sympy import *

m1 = 1 # минимальное значение производной на отрезке

itters = 0
sp_x = []
sp_f = []

def f(x):
    return sin(1 - 0.2*x*x) - x

def chord_method(f, a, b, tolerance=1e-4):
    global itters
    fa = f(a)
    fb = f(b)
    с = -1
    fc = tolerance / m1 + 1000 
    while (abs(fc) >= tolerance / m1):

        c = (a * fb - b * fa) / (fb - fa)
        fc = f(c)

        itters += 1
        sp_x.append(с)
        sp_f.append(fc)

        if fc * fa < 0:
            b = c
            fb = fc
        else:
            a = c
            fa = fc
    return с



root = chord_method(f, a=0, b=2)
print(itters)
df = pd.DataFrame(data={'n':range(itters), 'x': sp_x, 'f(x)': sp_f})
print(df)