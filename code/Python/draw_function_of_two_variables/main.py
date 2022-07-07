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
THETA = np.arange(-0.06 * np.pi, 0.06 * np.pi, 0.2)
YITA = random.random()

RESULT = []
for j in range(len(V)):
    for i in range(len(THETA)):
        y = (np.cos(
            THETA[i] + np.arctan(V[j] * np.sin(THETA[i]) / (YITA * (V[j] + V[j] * np.cos(THETA[i])))))) - np.cos(
            THETA[i] - np.arctan(V[j] * np.sin(THETA[i]) / (YITA * (V[j] - V[j] * np.cos(THETA[i])))))
        dx = THETA[1] - THETA[0]
        fArea = np.sum(y * dx)
        RESULT.append(fArea)
        # print("Integral area:", fArea)


# print(RESULT[len(RESULT) - 1])

def cal_integration(v, mu):
    f = lambda theta: np.cos(theta + np.arctan(v * np.sin(theta) / YITA * (v + v * np.cos(theta)))) - np.cos(
        theta - np.arctan(v * np.sin(theta) / (YITA * (v - v * np.cos(theta)))))
    integration = integrate.quad(f, 0, np.pi / 2)
    return -1 * integration * (1 / np.pi) * mu * M * G


RESULT = np.array(RESULT).reshape(len(THETA), len(V))
print(RESULT)

print("length of THETA:", len(THETA))
print("length of V:", len(V))
print("shape of RESULT:", shape(RESULT))

DRAW_RESULT = [V, THETA.tolist()]
print(DRAW_RESULT)



def main():



if __name__ == '__main__':
    main()
