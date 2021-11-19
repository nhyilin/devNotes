#!C:\Users\yilin\.conda\envs\vtk_develop\python
import os
import csv
import vtk
from sys import path, version_info
import numpy as np
import statistics
import math
import datetime
from pathlib import Path

#----------pubFunctions-------#

def writePointsData(path):
    pointName = Path(path)
    pointName.stem
    #----------pubFunctions-------#
    # path = "/Users/peiyilin/code/VSCode/goldFinger/1/A.csv"

    def getNum(x):
        with open(path) as csv_file:
            row = csv.reader(csv_file)
            next(row)
            numbers = []
            for r in row:
                numbers.append(float(r[x]))
        return numbers
    def meanOriginalPoint(colum):
        tf_T = getNum(colum)
        mean_tf_T = statistics.mean(tf_T)
        return mean_tf_T
    def varianceOriginalPoint(colum):
        tf_T = getNum(colum)
        variance_tf_T = statistics.variance(tf_T)
        return variance_tf_T
    #----------TestFinger-------#
    mean_tf_Tx = meanOriginalPoint(9)
    mean_tf_Ty = meanOriginalPoint(10)
    mean_tf_Tz = meanOriginalPoint(11)
    variance_tf_Tx = varianceOriginalPoint(9)
    variance_tf_Ty = varianceOriginalPoint(10)
    variance_tf_Tz = varianceOriginalPoint(11)

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
    quaternion = list(zip(sp_Q0, sp_Qx, sp_Qy, sp_Qz))
    quaternion = np.array(quaternion).reshape(len(bias),4)

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

    def meanSharpProbe(columOfSum):
        mean_sum = statistics.mean(columOfSum)
        return mean_sum
    def varianceSharpProbe(columOfSum):
        variance_sum = statistics.variance(columOfSum)
        return variance_sum

    mean_sumX = meanSharpProbe(sumX)
    mean_sumY = meanSharpProbe(sumY)
    mean_sumZ = meanSharpProbe(sumZ)
    variance_sumX = varianceSharpProbe(sumX)
    variance_sumY = varianceSharpProbe(sumY)
    variance_sumZ = varianceSharpProbe(sumZ)

    d_x = mean_sumX - mean_tf_Tx
    d_y = mean_sumY - mean_tf_Ty
    d_z = mean_sumZ - mean_tf_Tz
    distance = math.sqrt(d_x**2 + d_y**2 + d_z**2)

    # rpath = "/Users/peiyilin/code/VSCode/goldFinger/test01/result.csv"
    # with open(rpath, 'a+', encoding='utf-8-sig') as csvfile:         #以写入模式打开csv文件，如果没有csv文件会自动创建。
    #     writer = csv.writer(csvfile)
    #     if pointName.stem == 'A':
    #         writer.writerow(["点","tx均值","ty均值","tz均值","tx方差","ty方差","tz方差","cx均值","cy均值","cz均值","cx方差","cy方差","cz方差","两点距离"])
    #         writer.writerow([pointName.stem,mean_tf_Tx,mean_tf_Ty,mean_tf_Tz,variance_tf_Tx,variance_tf_Ty,variance_tf_Tz,mean_sumX,mean_sumY,mean_sumZ,variance_sumX,variance_sumY,variance_sumZ,distance])
    #     else:
    #         writer.writerow([pointName.stem,mean_tf_Tx,mean_tf_Ty,mean_tf_Tz,variance_tf_Tx,variance_tf_Ty,variance_tf_Tz,mean_sumX,mean_sumY,mean_sumZ,variance_sumX,variance_sumY,variance_sumZ,distance])

    rpath = "E:/tmc/vtk_development/goldFinger/test01/result.csv"
    with open(rpath, 'a+', encoding='utf-8-sig') as csvfile:         #以写入模式打开csv文件，如果没有csv文件会自动创建。
        writer = csv.writer(csvfile)
        if pointName.stem == 'A':
            writer.writerow(["点","tx均值","ty均值","tz均值","tx方差","ty方差","tz方差","cx均值","cy均值","cz均值","cx方差","cy方差","cz方差","两点距离"])
            writer.writerow([pointName.stem,mean_tf_Tx,mean_tf_Ty,mean_tf_Tz,variance_tf_Tx,variance_tf_Ty,variance_tf_Tz,mean_sumX,mean_sumY,mean_sumZ,variance_sumX,variance_sumY,variance_sumZ,distance])
        else:
            writer.writerow([pointName.stem,mean_tf_Tx,mean_tf_Ty,mean_tf_Tz,variance_tf_Tx,variance_tf_Ty,variance_tf_Tz,mean_sumX,mean_sumY,mean_sumZ,variance_sumX,variance_sumY,variance_sumZ,distance])


folder = "E:/tmc/vtk_development/goldFinger/1"
fileList = ['A.csv','B.csv','C.csv','D.csv','E.csv','F.csv']
for filename in fileList:
    path = os.path.join(folder,filename)
    writePointsData(path)


print("finishing time: ", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

