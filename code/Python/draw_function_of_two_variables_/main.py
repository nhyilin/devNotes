from sympy import *
import math
from scipy.integrate import quad
import random
from scipy import integrate
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import scipy.integrate

# 论文中为投掷后的分数与投掷角度、速度的函数
# 本文为速度与摩擦系数、角度的函数
M = float(19.96)
G = float(9.8)
MU = np.arange(0.05, 0.1, 0.01).tolist()
# MU = list(range(0.05, 0.1, 0.01))
V = np.arange(1.8, 3.2, 0.1).tolist()
THETA = np.arange(-0.06 * np.pi, 0.06 * np.pi, 0.02).tolist()
YITA = random.random()


def cal_integration(v, mu):
    f = lambda theta: np.cos(theta + np.arctan(v * np.sin(theta) / YITA * (v + v * np.cos(theta)))) - np.cos(
        theta - np.arctan(v * np.sin(theta) / (YITA * (v - v * np.cos(theta)))))
    integration = list(integrate.quad(f, 0, np.pi / 2))
    integration = integration[0]
    integration = float(-1) * float(1 / np.pi) * mu * M * G * integration
    return integration


# print(cal_integration(1,2))
# RESULT = np.array([])
RESULT = []
for i in range(len(MU)):
    for j in range(len(V)):
        RESULT.append(i)
        RESULT.append(j)
        RESULT.append(cal_integration(V[j], MU[i]))
RESULT = np.array(RESULT).reshape(len(MU)*len(V), 3)
RESULT_MU = [RESULT[:, 0]]
RESULT_V = [RESULT[:, 1]]
RESULT_F = [RESULT[:, 2]]
# print(RESULT)
# print(shape(RESULT))

# print("length of THETA:", len(THETA))
# print("length of V:", len(V))
# print("shape of RESULT:", shape(RESULT))

# DRAW_RESULT = [V, THETA.tolist()]
# print(DRAW_RESULT)



fig = plt.figure()
ax = Axes3D(fig,auto_add_to_figure=False)
fig.add_axes(ax)

ax.scatter(RESULT_MU,RESULT_V,RESULT_F) # 画出(xs1,ys1,zs1)的散点图。
ax.scatter(RESULT_MU,RESULT_V,RESULT_F,c='r',marker='^')
ax.scatter(RESULT_MU,RESULT_V,RESULT_F,c='g',marker='*')

ax.set_xlabel('MU label') # 画出坐标轴
ax.set_ylabel('V label')
ax.set_zlabel('F label')

plt.show()