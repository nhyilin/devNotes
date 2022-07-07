from sympy import *
import numpy as np
import random
from scipy import integrate
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 论文中为投掷后的分数与投掷角度、速度的函数
# 本文为速度与摩擦系数、角度的函数

M = float(19.96)
G = float(9.8)
# MU = [0.0625, 0.25, 0.5]
MU = [1, 2, 3]
V = np.arange(1.8, 3.2, 0.01).tolist()
THETA = np.arange(-0.06 * np.pi, 0.06 * np.pi, 0.002).tolist()
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
        RESULT.append(MU[i])
        RESULT.append(V[j])
        RESULT.append(cal_integration(V[j], MU[i]))
RESULT = np.array(RESULT).reshape(len(MU) * len(V), 3)
print(RESULT, "\n -------------------RESULT-------------------")
# RESULT_MU = RESULT[:, 0]
# RESULT_V = RESULT[:, 1]
# RESULT_F = RESULT[:, 2]

RESULT_01 = RESULT[0: len(V)]  # 截取V长度的计算结果作为mu01参数，此处长度计算应为len(V)*len(MU)/3，但是语法好像不支持，正好len(MU)=3，所以这么写
RESULT_02 = RESULT[len(V): 2 * len(V)]
RESULT_03 = RESULT[2 * len(V): 3 * len(V)]
print(RESULT_01, "\n -------------------RESULT_01-------------------")
print(RESULT_02, "\n -------------------RESULT_02-------------------")
print(RESULT_03, "\n -------------------RESULT_03-------------------")
# RESULT_MU = RESULT_MU.reshape(3, len(RESULT)/3)

# print([RESULT_MU[:,len(RESULT_V)]])#RESULT_MU_01
# print(RESULT)
# print(shape(RESULT))

# print("length of THETA:", len(THETA))
# print("length of V:", len(V))
# print("shape of RESULT:", shape(RESULT))

# DRAW_RESULT = [V, THETA.tolist()]
# print(DRAW_RESULT)


# fig = plt.figure()
# ax = Axes3D(fig, auto_add_to_figure=False)
# fig.add_axes(ax)
#
# ax.scatter(RESULT_MU, RESULT_V, RESULT_F, c='r')#, marker='*'
#
# ax.set_xlabel('MU label')  # 画出坐标轴
# ax.set_ylabel('V label')
# ax.set_zlabel('F label')
# plt.show()


plt.style.use('ggplot')
plt.figure('relation between F & mu & v')

plt.plot(RESULT_01[:, 1], RESULT_01[:, 2], 'ro') # 绘制 RESULT_01 的后两列，分别为 V 和 F
plt.plot(RESULT_02[:, 1], RESULT_02[:, 2], 'b') # MU2
plt.plot(RESULT_03[:, 1], RESULT_03[:, 2], 'g') # MU3
plt.style.use('ggplot')

plt.draw()  # 显示绘图
plt.show()
