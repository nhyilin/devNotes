import os
import math
import pylab
import numpy as np
from scipy import stats
import matplotlib as mpl
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import FuncFormatter

# 读取obj数据
objFilePath = '/Users/peiyilin/HURWA/2.4/bound/10.obj'
with open(objFilePath, 'r') as file:
    points = []
    ts = []
    while 1:
        line = file.readline()
        if not line:
            break
        strs = line.split(" ")
        if strs[0] == "v":
            points.append((float(strs[1]), float(strs[2]), float(strs[3])))
            ts.append((float(strs[1]), float(strs[2]), float(strs[3])))

# *********************************************************
# *********************************************************


# 读取wall数据

wallPath = '/Users/peiyilin/HURWA/2.4/bound/10VirtualWall.txt'
with open(wallPath, 'r') as file:
    next(file)
    next(file)
    walls = []
    while 1:
        line = file.readline()
        if not line:
            break
        strs = line.split(",")
        strs = np.array(strs)
        walls.append((float(strs[0]), float(strs[1]), float(strs[2])))
#        print(strs)


print('walls is :', walls)
# *********************************************************
# *********************************************************


# points原本为列表，需要转变为矩阵，方便处理
targets = np.array(points)
ts = np.array(ts)
objs = len(targets)

# 定义obj点阵，为坐标转换前的描点准备
tx = targets[:, 0]
ty = targets[:, 1]
tz = targets[:, 2]

# wall点
w1 = np.array(walls[0])
w2 = np.array(walls[1])
w3 = np.array(walls[2])
w4 = np.array(walls[3])

# These two vectors are in the plane
v1 = w3 - w2
v2 = w3 - w1

# 叉积
cp = np.cross(v1, v2)
a, b, c = cp

# This evaluates a * x3 + b * y3 + c * z3 which equals d
d = np.dot(cp, w3)

# 打印方程式 print('The equation is {0}x + {1}y + {2}z = {3}'.format(a, b, c, d))
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# plot the original points. We use zip to get 1D lists of x, y and z. coordinates.
ax.plot(*zip(w1, w2, w3), color='r', marker='o')
ax.plot(tx, ty, tz, color='g', linestyle=' ', marker='o')

# adjust the view so we can see the point/plane alignment
ax.view_init(0, 22)
plt.tight_layout()
# plt.savefig('plane.png')
# plt.show()


# 求新坐标系三个轴的对应向量，以w1为原点,w1到w2为x轴正方向,z轴垂直于w1/w2/w3所在平面
norm = np.linalg.norm(v1)
newX = v1 / norm

norm = np.linalg.norm(cp)
newZ = cp / norm

# print(newX.dot(newZ))
newY = np.cross(newZ, newX)
# print(newX.dot(newY))


# 新坐标系到原坐标系的转换矩阵
mNew2Base = np.vstack((newX, newY, newZ, w2)).T  # reshape(3,3)
# print("mNew2Base：", mNew2Base)
msquare = np.vstack((mNew2Base, np.array([0, 0, 0, 1]).reshape(1, 4)))

# print('aaaaa', np.array([0,0,0,1]).reshape(1,4))
# print('bbbbb', np.array([0,0,0,1]))

# 原坐标到新坐标系的转化矩阵
mBase2New = np.linalg.inv(msquare)

# 坐标转换前，添加单位列,转换为ts
# print('the number of obj data:', objs)
index = 0
ts = []
ts = np.array([])
while index < objs:
    # ts[index] 
    a = np.append(points[index], 1)
    ts = np.append(ts, a)
    index = index + 1
else:
    quit
#    print ("Complete the traversal sequence")


ts = ts.reshape(ts.shape[0] // 4, 4)

##函数运算点，坐标转换
# 计算函数mBase2New.dot(a5)

# print("validation:")
newdot = []
newdot = np.array([])
d = 0
while d < objs:
    # print(ts[d].shape, ts.shape)
    b = mBase2New.dot(ts[d])
    newdot = np.append(newdot, b)
    d = d + 1
#    print(newdot)
#    print(b)
else:
    quit
#    print ("Complete dots calculation")

newdot = newdot.reshape(newdot.shape[0] // 4, 4)
# print(newdot.shape)
# print(b.shape)

nx = newdot[:, 0]
ny = newdot[:, 1]
nz = newdot[:, 2]
# print('nx are', nx)


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# *********************************************************
# *********************************************************

# differences betwween list & array
w_ = [w1, w2, w3, w4]
# print('w_ is', w_)
w_ = np.array(w_)
# print('w_ is', w_)

# *********************************************************
# *********************************************************
# add row "1" to the 4 walls dots & transfering the 4 walls dots
h = 0
w = []
while h < 4:
    x = np.append(w_[h], 1)
    y = mBase2New.dot(x)
    w = np.append(w, y)
    h = h + 1
else:
    quit
#    print ("Complete calculating to walls")


w = w.reshape(w.shape[0] // 4, 4)
wx = w[:, 0]
wy = w[:, 1]
wz = w[:, 2]
# print('w:', w)
# print('wx:', wx)


# ax.plot(nx, ny, nz, color='g', marker='.')
ax.scatter(nx, ny, nz, color='g', marker='.')
ax.plot(wx, wy, wz, color='c', marker='o')
ax.spines['bottom'].set_position(('data', 0))
ax.xaxis.set_ticks_position('bottom')
# ax.plot(p1, p2, p3, p4, color='g', marker='o')

# Two-dimensional image
ax.scatter(nx, ny, c='r', s=20, alpha=0.5)

# adjust the view so we can see the point/plane alignment
ax.view_init(0, 22)
# ax.set_box_aspect((np.ptp(nx), np.ptp(ny), np.ptp(nz)))
plt.tight_layout()
# plt.savefig('newplane.png')
plt.show()

# *********************************************************
# *********************************************************


res = stats.linregress(nx, ny)
# print(f"R-squared: {res.rvalue**2:.6f}")

plt.plot([wx[1], wx[2]], [wy[1], wy[2]], 'b', label='walls line')
plt.plot(nx, ny, '.', c='pink', markersize=1, label='objs data')
plt.plot(nx, res.intercept + res.slope * nx, 'r', label='fitted line')
plt.axis('equal')
plt.legend()
plt.show()

# *********************************************************
# *********************************************************
# k = res.slope

k = abs(res.slope)
k1 = abs(res.slope)
k = float(format(k, '.3f'))
# k = format(k, '.3f')
b = abs(res.intercept)
b = float(format(b, '.3f'))
# print('k is:', k)
# print('b is:', b)
print('the line is :', 'y = ', k, '* x +', b)
print(chr(952), 'is:', math.atan(k1))

print('ALL DONE!')






