#!/Users/peiyilin/opt/anaconda3/envs/vtk_test/bin/python
import os
import csv
import vtk
from sys import path, version_info
import numpy as np
import statistics
import math

#----------pubFunctions-------#
path = "/Users/peiyilin/code/VSCode/goldFinger/1/a.csv"
def getNum(x):
    with open(path) as csv_file:
        row = csv.reader(csv_file)
        next(row)
        numbers = []
        for r in row:
            numbers.append(float(r[x]))
    return numbers

def originalPoint(colum):
    tf_T = getNum(colum)
    mean_tf_T = statistics.mean(tf_T)
    variance_tf_T = statistics.variance(tf_T)
    return mean_tf_T

#----------TestFinger-------#

mean_tf_Tx = originalPoint(9)
mean_tf_Ty = originalPoint(10)
mean_tf_Tz = originalPoint(11)

#----------SharpProbe-------#
sp_Q0 = getNum(34)
sp_Qx = getNum(35)
sp_Qy = getNum(36)
sp_Qz = getNum(37)
sp_Tx = getNum(38)
sp_Ty = getNum(39)
sp_Tz = getNum(40)
vector = [0, -121, 0]
bias = list(zip(sp_Tx, sp_Ty, sp_Tz))
bias = np.array(bias)
# print("------bias is ------\n", bias)
quaternion = list(zip(sp_Q0, sp_Qx, sp_Qy, sp_Qz))
quaternion = np.array(quaternion).reshape(len(bias),4)
# print("------quaternion is------ \n",quaternion)

# 将旧向量在四元数作用下旋转 #
newVector = []
for i in range(len(quaternion)):
    rotate = vtk.vtkMath()
    ans = [0, 0, 0]
    rotate.RotateVectorByNormalizedQuaternion(vector, quaternion[i], ans)
    newVector.append(ans)
newVector = np.array(newVector)

index = 0
sum = []
for index in range(len(bias)):
    sum.append(bias[index] + newVector[index])
sum = np.array(sum).reshape(len(bias),3)
sumX = sum[: , 0]
sumY = sum[: , 1]
sumZ = sum[: , 2]

def SharpProbe(columOfSum):
    mean_sumX = statistics.mean(columOfSum)
    variance_sumX = statistics.variance(columOfSum)
    return mean_sumX

mean_sumX = SharpProbe(sumX)
mean_sumY = SharpProbe(sumY)
mean_sumZ = SharpProbe(sumZ)

d_x = mean_sumX - mean_tf_Tx
d_y = mean_sumY - mean_tf_Ty
d_z = mean_sumZ - mean_tf_Tz

distance = math.sqrt(d_x**2 + d_y**2 + d_z**2)
print("------distance is------\n", distance)
