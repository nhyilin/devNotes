# #!/Users/peiyilin/opt/anaconda3/envs/vtk_test/bin/python
import os
import csv
import vtk
from sys import path, version_info
import numpy as np
import statistics
import math
import datetime

#----------pubFunctions-------#
path = "/Users/peiyilin/code/VSCode/goldFinger/1/a.csv"

def getNum(path,x):
    with open(path) as csv_file:
        row = csv.reader(csv_file)
        next(row)
        numbers = []
        for r in row:
            numbers.append(float(r[x]))
    return numbers
def meanOriginalPoint(path,colum):
    tf_T = getNum(path,colum)
    mean_tf_T = statistics.mean(tf_T)
    return mean_tf_T
def varianceOriginalPoint(path,colum):
    tf_T = getNum(colum)
    variance_tf_T = statistics.variance(tf_T)
    return variance_tf_T
#----------TestFinger-------#
mean_tf_Tx = meanOriginalPoint(path,9)
mean_tf_Ty = meanOriginalPoint(path,10)
mean_tf_Tz = meanOriginalPoint(path,11)
variance_tf_Tx = varianceOriginalPoint(path,9)
variance_tf_Ty = varianceOriginalPoint(path,10)
variance_tf_Tz = varianceOriginalPoint(path,11)

mean_tf_Tx02 = meanOriginalPoint(path02,9)
mean_tf_Ty02 = meanOriginalPoint(path02,10)
mean_tf_Tz02 = meanOriginalPoint(path02,11)
variance_tf_Tx02 = varianceOriginalPoint(path02,9)
variance_tf_Ty02 = varianceOriginalPoint(path02,10)
variance_tf_Tz02 = varianceOriginalPoint(path02,11)

mean_tf_Tx03 = meanOriginalPoint(path03,9)
mean_tf_Tx03 = meanOriginalPoint(path03,9)
mean_tf_Ty03 = meanOriginalPoint(path03,10)
mean_tf_Tz03 = meanOriginalPoint(path03,11)
variance_tf_Tx03 = varianceOriginalPoint(path03,9)
variance_tf_Ty03 = varianceOriginalPoint(path03,10)
variance_tf_Tz03 = varianceOriginalPoint(path03,11)

mean_tf_Tx04 = meanOriginalPoint(path04,9)
mean_tf_Ty04 = meanOriginalPoint(path04,10)
mean_tf_Tz04 = meanOriginalPoint(path04,11)
variance_tf_Tx04 = varianceOriginalPoint(path04,9)
variance_tf_Ty04 = varianceOriginalPoint(path04,10)
variance_tf_Tz04 = varianceOriginalPoint(path04,11)

mean_tf_Tx05 = meanOriginalPoint(path05,9)
mean_tf_Ty05 = meanOriginalPoint(path05,10)
mean_tf_Tz05 = meanOriginalPoint(path05,11)
variance_tf_Tx05 = varianceOriginalPoint(path05,9)
variance_tf_Ty05 = varianceOriginalPoint(path05,10)
variance_tf_Tz05 = varianceOriginalPoint(path05,11)

mean_tf_Tx06 = meanOriginalPoint(path06,9)
mean_tf_Ty06 = meanOriginalPoint(path06,10)
mean_tf_Tz06 = meanOriginalPoint(path06,11)
variance_tf_Tx06 = varianceOriginalPoint(path06,9)
variance_tf_Ty06 = varianceOriginalPoint(path06,10)
variance_tf_Tz06 = varianceOriginalPoint(path06,11)
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

mean_sumX02 = meanSharpProbe(sumX)
mean_sumY02 = meanSharpProbe(sumY)
mean_sumZ02 = meanSharpProbe(sumZ)
variance_sumX02 = varianceSharpProbe(sumX)
variance_sumY02 = varianceSharpProbe(sumY)
variance_sumZ02 = varianceSharpProbe(sumZ)

mean_sumX03 = meanSharpProbe(sumX)
mean_sumY03 = meanSharpProbe(sumY)
mean_sumZ03 = meanSharpProbe(sumZ)
variance_sumX03 = varianceSharpProbe(sumX)
variance_sumY03 = varianceSharpProbe(sumY)
variance_sumZ03 = varianceSharpProbe(sumZ)

mean_sumX04 = meanSharpProbe(sumX)
mean_sumY04 = meanSharpProbe(sumY)
mean_sumZ04 = meanSharpProbe(sumZ)
variance_sumX04 = varianceSharpProbe(sumX)
variance_sumY04 = varianceSharpProbe(sumY)
variance_sumZ04 = varianceSharpProbe(sumZ)

mean_sumX05 = meanSharpProbe(sumX)
mean_sumY05 = meanSharpProbe(sumY)
mean_sumZ05 = meanSharpProbe(sumZ)
variance_sumX05 = varianceSharpProbe(sumX)
variance_sumY05 = varianceSharpProbe(sumY)
variance_sumZ05 = varianceSharpProbe(sumZ)

mean_sumX06 = meanSharpProbe(sumX)
mean_sumY06 = meanSharpProbe(sumY)
mean_sumZ06 = meanSharpProbe(sumZ)
variance_sumX06 = varianceSharpProbe(sumX)
variance_sumY06 = varianceSharpProbe(sumY)
variance_sumZ06 = varianceSharpProbe(sumZ)

def distance(x1,x2,y1,y2,z1,z2):
    d_x = x1 - x2
    d_y = y1 - y2
    d_z = z1 - z2
    distance = math.sqrt(d_x**2 + d_y**2 + d_z**2)
    return distance

distance = distance(mean_tf_Tx,mean_tf_Ty,mean_tf_Tz,mean_sumX,mean_sumY,mean_sumZ)
print(distance)
distance02 = distance(mean_tf_Tx02,mean_tf_Ty02,mean_tf_Tz02,mean_sumX02,mean_sumY02,mean_sumZ02)
distance03 = distance(mean_tf_Tx03,mean_tf_Ty03,mean_tf_Tz03,mean_sumX03,mean_sumY03,mean_sumZ03)
distance04 = distance(mean_tf_Tx04,mean_tf_Ty04,mean_tf_Tz04,mean_sumX04,mean_sumY04,mean_sumZ04)
distance05 = distance(mean_tf_Tx05,mean_tf_Ty05,mean_tf_Tz05,mean_sumX05,mean_sumY05,mean_sumZ05)
distance06 = distance(mean_tf_Tx06,mean_tf_Ty06,mean_tf_Tz06,mean_sumX06,mean_sumY06,mean_sumZ06)



rpath = "/Users/peiyilin/code/VSCode/goldFinger/1/x.csv"
with open(rpath, 'w', encoding='utf-8-sig') as csvfile:         #以写入模式打开csv文件，如果没有csv文件会自动创建。
    writer = csv.writer(csvfile)
    writer.writerow(["点","tx均值","ty均值","tz均值","tx方差","ty方差","tz方差","cx均值","cy均值","cz均值","cx方差","cy方差","cz方差","distance"])
    writer.writerow(["A",mean_tf_Tx,mean_tf_Ty,mean_tf_Tz,variance_tf_Tx,variance_tf_Ty,variance_tf_Tz,mean_sumX,mean_sumY,mean_sumZ,variance_sumX,variance_sumY,variance_sumZ,distance])
    writer.writerow(["B",mean_tf_Tx02,mean_tf_Ty02,mean_tf_Tz02,variance_tf_Tx02,variance_tf_Ty02,variance_tf_Tz02,mean_sumX02,mean_sumY02,mean_sumZ02,variance_sumX02,variance_sumY02,variance_sumZ02,distance])
    writer.writerow(["C",mean_tf_Tx03,mean_tf_Ty03,mean_tf_Tz03,variance_tf_Tx03,variance_tf_Ty03,variance_tf_Tz03,mean_sumX03,mean_sumY03,mean_sumZ03,variance_sumX03,variance_sumY03,variance_sumZ03,distance])
    writer.writerow(["D",mean_tf_Tx04,mean_tf_Ty04,mean_tf_Tz04,variance_tf_Tx04,variance_tf_Ty04,variance_tf_Tz04,mean_sumX04,mean_sumY04,mean_sumZ04,variance_sumX04,variance_sumY04,variance_sumZ04,distance])
    writer.writerow(["E",mean_tf_Tx05,mean_tf_Ty05,mean_tf_Tz05,variance_tf_Tx05,variance_tf_Ty05,variance_tf_Tz05,mean_sumX05,mean_sumY05,mean_sumZ05,variance_sumX05,variance_sumY05,variance_sumZ05,distance])
    writer.writerow(["F",mean_tf_Tx06,mean_tf_Ty06,mean_tf_Tz06,variance_tf_Tx06,variance_tf_Ty06,variance_tf_Tz06,mean_sumX06,mean_sumY06,mean_sumZ06,variance_sumX06,variance_sumY06,variance_sumZ06,distance])





print(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

