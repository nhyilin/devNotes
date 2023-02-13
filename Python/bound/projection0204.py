import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D

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
        # if strs[0] == "p":
        #     break
# points原本为列表，需要转变为矩阵，方便处理
targets = np.array(points)
ts = np.array(ts)
objs = len(targets)

#定义obj点阵，为坐标转换前的描点准备
tx = targets[:,0]
ty = targets[:,1]
tz = targets[:,2]

#wall点
w1 = np.array([173.3697098039625, 136.73933646095352, 567.0089151851672])
w2 = np.array([183.91388441096436, 135.52840190148825, 573.4607583243743])
w3 = np.array([265.13260392604803, 124.19853000288016, 575.0958291154589])
w4 = np.array([282.2593438459163, 121.8523339451749, 576.47162244842])

#取自obj的测试点，转换坐标之前
ts1 = targets[0]
ts2 = targets[1]
ts3 = targets[2]
ts4 = targets[3]
ts5 = targets[4]


# These two vectors are in the plane
v1 = w2 - w1
v2 = w3 - w1

#叉积
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
plt.savefig('plane.pdf')
#plt.show()


# 求新坐标系三个轴的对应向量，以w1为原点,w1到w2为x轴正方向,z轴垂直于w1/w2/w3所在平面
norm = np.linalg.norm(v1)
newX = v1/norm

norm = np.linalg.norm(cp)
newZ = cp/norm


print(newX.dot(newZ))
newY=np.cross(newZ, newX)
print(newX.dot(newY))

# todo 
#print("newX", newX)
#print("newY", newY)
#print("newZ", newZ)


# 新坐标系到原坐标系的转换矩阵
mNew2Base = np.vstack((newX, newY, newZ, w1)).T  # reshape(3,3)
#print("mNew2Base", mNew2Base)
msquare = np.vstack((mNew2Base, np.array([0,0,0,1]).reshape(1,4)))

# 原坐标到新坐标系的转化矩阵
mBase2New = np.linalg.inv(msquare)
#print("mBase2New", mBase2New)



# 坐标转换前，添加单位列,转换为ts
#print('the number of obj data:', objs)
index = 0
ts = []
ts = np.array([])
while index < objs:
    # ts[index] 
    a = np.append(points[index],1)
    ts = np.append(ts, a)
    index = index + 1
else:
    print ("Complete the traversal sequence")




ts = ts.reshape(ts.shape[0]//4,4)

##函数运算点，坐标转换
# 计算函数mBase2New.dot(a5)

#print("validation:")
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
    print ("End of dots calculation")  

newdot= newdot.reshape(newdot.shape[0]//4,4)
#print(newdot.shape)
#print(b.shape)

nx = newdot[:,0]
ny = newdot[:,1]
nz = newdot[:,2]
#print('nx are', nx)


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


#******************************************************************************************************************************#
#differences betwween list & array
w_ = [w1,w2,w3,w4]
w_ = np.array(w_)

#******************************************************************************************************************************#
# add row "1" to the 4 walls dots & transfering the 4 walls dots
h = 0
w = []
while h < 4 :
    x = np.append(w[h],1)
    y = mBase2New.dot(x)
    w_ = np.append(w, y)
    h = h + 1
    print('w', w)
else:
    print ("finish calculating to walls")

print('w_ is', w_)


ax.plot(nx, ny, nz, color='g', marker='o')
#ax.plot(p1, p2, p3, p4, color='g', marker='o')



# adjust the view so we can see the point/plane alignment
ax.view_init(0, 22)
ax.set_box_aspect((np.ptp(nx), np.ptp(ny), np.ptp(nz)))
plt.tight_layout()
plt.savefig('newplane.pdf')
#plt.show()


print('DONE!')






