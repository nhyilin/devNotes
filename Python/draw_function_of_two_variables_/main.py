from sympy import *
import numpy as np
import random
from scipy import integrate
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 论文中为投掷后的分数与投掷角度、速度的函数
# 本文为速度与摩擦系数、角度的函数
# 代码中大写变量为数组，小写为对应变量中的具体数值

# 常量定义
M = float(19.96)
G = float(9.8)
MU = [0.0625, 0.25, 0.5]
V = np.arange(1.8, 3.2, 0.01).tolist()
THETA = np.arange(-0.06 * np.pi, 0.06 * np.pi, 0.002).tolist()
YITA = random.random()


# 这是一个计算积分的函数，返回值为一个float类型数据，输入值为v和mu两个float类型数据
def cal_integration(v, mu):
    f = lambda theta: np.cos(theta + np.arctan(v * np.sin(theta) / YITA * (v + v * np.cos(theta)))) - np.cos(
        theta - np.arctan(v * np.sin(theta) / (YITA * (v - v * np.cos(theta)))))
    integration = list(integrate.quad(f, 0, np.pi / 2))
    integration = integration[0]
    integration = float(-1) * float(1 / np.pi) * mu * M * G * integration
    return integration


RESULT = []  # RESULT里将要存放所有计算结果的集合，下面的print函数可以查看其中的计算结果
for i in range(len(MU)):  # 这个嵌套的for循环会便利所有MU和V的组合并放入积分函数计算
    for j in range(len(V)):
        RESULT.append(MU[i])
        RESULT.append(V[j])
        RESULT.append(cal_integration(V[j], MU[i]))  # 三个append依次将参加计算的MU
RESULT = np.array(RESULT).reshape(len(MU) * len(V), 3)
print("\n -------------------RESULT-------------------\n, RESULT")  # 打印log检查结果是否正确

RESULT_01 = RESULT[0: len(V)]  # 截取V长度的计算结果作为mu01参数，此处长度计算应为len(V)*len(MU)/3，但是语法好像不支持，正好len(MU)=3，所以这么写
RESULT_02 = RESULT[len(V): 2 * len(V)]
RESULT_03 = RESULT[2 * len(V): 3 * len(V)]
print("\n -------------------RESULT_01-------------------", RESULT_01)  # 打印log检查结果是否正确
print("\n -------------------RESULT_02-------------------", RESULT_02)
print("\n -------------------RESULT_03-------------------", RESULT_03)

# 绘图部分
plt.style.use('ggplot')
plt.figure('F & mu & v')
plt.title("relation between F & mu & v")
plt.xlabel("V - label")
plt.ylabel("F - label")

plt.scatter(RESULT_01[:, 1], RESULT_01[:, 2], label='MU = 0.0625', ls='-')  # 绘制 RESULT_01 的后两列，分别为 V 和 F
plt.scatter(RESULT_02[:, 1], RESULT_02[:, 2], label='MU = 0.25', ls='-.')  # MU2
plt.scatter(RESULT_03[:, 1], RESULT_03[:, 2], label='MU = 0.5', ls='-.')  # MU3
plt.legend()

plt.draw()
plt.show()  # 显示绘图
