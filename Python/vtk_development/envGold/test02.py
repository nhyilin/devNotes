import os
import csv
import vtk
import math
import datetime
import statistics
import numpy as np
import pandas as pd
from pathlib import Path
from sys import path, version_info


def pointInfo(path, colsNum, arrayCols):
    df = pd.read_csv(path, encoding='utf-8', header=None)
    cols_data = df.iloc[1:, colsNum:colsNum + arrayCols]
    data_list = np.array(cols_data)
    data_list = data_list.astype(float)# numpy强制类型转换
    originPoint = pointInfo(path, 9, arrayCols)
    quaternion = pointInfo(path, 34, arrayCols+1)
    bias = pointInfo(path, 38, arrayCols)
    return data_list,originPoint,quaternion,bias

rotationVector = [0, -121, 0]

rotatedVector = []
for i in range(len(pointInfo[2])):
    rotate = vtk.vtkMath()
    ans = [0, 0, 0]
    rotate.RotateVectorByNormalizedQuaternion(rotationVector, pointInfo[2][i], ans)
    rotatedVector = np.array(rotatedVector.append(ans))
rotatedVector = np.array(rotatedVector)

index = 0
goldFingerPoint = []
for index in range(len(bias)):
    goldFingerPoint.append(bias[index] + rotatedVector[index])
goldFingerPoint = np.array(goldFingerPoint).reshape(len(bias), 3)

d_x = statistics.mean(goldFingerPoint[:, 0] - originPoint[:, 0])
d_y = statistics.mean(goldFingerPoint[:, 1] - originPoint[:, 1])
d_z = statistics.mean(goldFingerPoint[:, 2] - originPoint[:, 2])
distance = math.sqrt(d_x ** 2 + d_y ** 2 + d_z ** 2)

# def info2csv(distance, goldFingerPoint, originPoint, pointName, writer):
#     writer.writerow([pointName.stem, statistics.mean(originPoint[:, 0]), statistics.mean(originPoint[:, 1]),
#                      statistics.mean(originPoint[:, 2]), statistics.variance(originPoint[:, 0]),
#                      statistics.variance(originPoint[:, 1]), statistics.variance(originPoint[:, 2]),
#                      statistics.mean(goldFingerPoint[:, 0]), statistics.mean(goldFingerPoint[:, 1]),
#                      statistics.mean(goldFingerPoint[:, 2]), statistics.variance(goldFingerPoint[:, 0]),
#                      statistics.variance(goldFingerPoint[:, 1]), statistics.variance(goldFingerPoint[:, 2]),
#                      distance])


def readAndWritePoint2csv(path):
    witePath = "E:/tmc/vtk_development/goldFinger/test01/refactor.csv"
    pointName = Path(path)
    pointInfo(path, colsNum, arrayCols)
    with open(witePath, 'a+', encoding='utf-8-sig', newline="") as csvfile:
        writer = csv.writer(csvfile)
        if pointName.stem == 'A':
            writer.writerow(
                ["点", "tx均值", "ty均值", "tz均值", "tx方差", "ty方差", "tz方差", "cx均值", "cy均值", "cz均值", "cx方差", "cy方差", "cz方差",
                 "两点距离"])
            writer.writerow([pointName.stem])
        else:
            writer.writerow([pointName.stem])

folder = "E:\\tmc\\vtk_development\\goldFinger\\1"
fileList = ['A.csv','B.csv','C.csv','D.csv','E.csv','F.csv']
for filename in fileList:
    path = os.path.join(folder,filename)
    readAndWritePoint2csv(path)






print("finishing time: ", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))