from sympy import *
import math
from scipy.integrate import quad
import random
from scipy import integrate
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

# 论文中为投掷后的分数与投掷角度、速度的函数
# 本文为速度与摩擦系数、角度的函数
M = 19.96
G = 9.8
MU = np.arange(0.05, 0.1, 0.01)
V = np.arange(1.8, 3.2, 0.1)
THETA = np.arange(-0.06 * np.pi, 0.06 * np.pi, 0.02)
YITA = random.random()

fig = plt.figure()
ax = Axes3D(fig, auto_add_to_figure=False)
fig.add_axes(ax)
x = np.arange(-2 * np.pi, 2 * np.pi, 0.1)
y = np.arange(-2 * np.pi, 2 * np.pi, 0.1)
X, Y = np.meshgrid(x, y)  # 网格的创建，这个是关键
Z = np.sin(X) * np.cos(Y)
plt.xlabel('x')
plt.ylabel('y')
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='rainbow')
plt.show()


x = THETA
y = (np.cos(THETA + np.arctan(V * np.sin(THETA) / (YITA * (V + V * np.cos(THETA)))))) - np.cos(THETA - np.arctan(V * np.sin(THETA) / (YITA * (V - V * np.cos(THETA)))))
dx = x[1] - x[0]
fArea = np.sum(y*dx)
print("Integral area:", fArea)

