import pandas as pd
import numpy as np
import plotly.graph_objects as go

from sympy import *

def f(x):
    return np.sin(1 - 0.2*x*x) - x

begin = -2
end = 7
step = 0.2
size = 1000
x = np.linspace(begin, end, size)
y_f = f(x)
fig = go.Figure() # layout_xaxis_range = [-2,6]
fig.add_trace(go.Scatter(x=[begin, end],
                         y=[0, 0],
                         name="Ось Х"))

fig.add_trace(go.Scatter(x=x,
                         y=y_f,
                         name="График функции"))

fig.update_layout(title="Построение графика функции",
                  xaxis_title="Значение аргумента",
                  yaxis_title="Значение функции",
                  margin=dict(l=10, r=70, t=50, b=0))

fig.show()