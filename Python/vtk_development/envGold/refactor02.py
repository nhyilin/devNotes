import os
import csv
import vtk
import math
import psutil
import datetime
import statistics
import numpy as np
from pathlib import Path

COLS_BASE = 9
COLS_QUATERNION = 34
COLS_BIAS = 38
POINTCOLS = 3
QUATERNION = 4
SHARP_X = 6
TEST_X = 0
TIP2CENTERONSHARPPROBE= [0, -121, 0]

def readFile(path, colsNum, arrayCols):
    with open(path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        column = [row for row in reader]

        column_data = []
        for i in range(arrayCols):
            for index in range(len(column)):
                column_data.append(column[index][colsNum])
                index = index + 1
            colsNum = colsNum + 1
            i = i + 1
    data_list = np.array(column_data)
    data_list = data_list.reshape(arrayCols,len(column))
    data_list = np.transpose(data_list)
    data_list = data_list.astype(float)
    return data_list

# readFile(testPath, COLS_QUATERNION, QUATERNION)

def rotateAndBias(quaternion,bias):
    rotatedVector = []
    for i in range(len(quaternion)):
        rotate = vtk.vtkMath()
        ans = [0, 0, 0]
        rotate.RotateVectorByNormalizedQuaternion(TIP2CENTERONSHARPPROBE, quaternion[i], ans)
        rotatedVector.append(ans)
    rotatedVector = np.array(rotatedVector)
    index = 0
    goldFingerPoint = []
    for index in range(len(bias)):
        goldFingerPoint.append(bias[index] + rotatedVector[index])
    goldFingerPoint = np.array(goldFingerPoint)
    return goldFingerPoint

def arrangeMeanAndVariance(path):
    testPoint = readFile(path,COLS_BASE,POINTCOLS)
    quaternion = readFile(path,COLS_QUATERNION,QUATERNION)
    bias = readFile(path,COLS_BIAS,POINTCOLS)
    goldFinger = rotateAndBias(quaternion,bias)

    dataManager = []
    index = 0
    for index in range(3):
        dataManager.append(statistics.mean(testPoint[:,index]))
    for index in range(3):
        dataManager.append(statistics.variance(testPoint[:, index]))
    for index in range(3):
        dataManager.append(statistics.mean(goldFinger[:, index]))
    for index in range(3):
        dataManager.append(statistics.variance(goldFinger[:, index]))
    return dataManager

def calcDistance(sharpPoint,basePoint):
    d_x = sharpPoint[0] - basePoint[0]
    d_y = sharpPoint[1] - basePoint[1]
    d_z = sharpPoint[2] - basePoint[2]
    distance = math.sqrt(d_x ** 2 + d_y ** 2 + d_z ** 2)
    return distance

def readAndWritePoint2csv(path,writer):
    pointName = Path(path)
    dataList = arrangeMeanAndVariance(path)

    sharpPoint = dataList[SHARP_X:SHARP_X+3]
    basePoint = dataList[TEST_X:TEST_X+3]
    distance = calcDistance(sharpPoint,basePoint)

    i = 0
    writeList = []
    for i in range(12):
        writeList.append(dataList[i])
    writeList.insert(0, pointName.stem)
    writeList.append(distance)

    writer.writerow(writeList)

def main():
    witePath = "E:/tmc/vtk_development/goldFinger/test01/refactor05.csv"
    with open(witePath, 'a+', encoding='utf-8-sig', newline="") as csvfile:
        csvWriter = csv.writer(csvfile)
        folder = "E:\\tmc\\vtk_development\\goldFinger\\1"
        fileList = ['A.csv', 'B.csv', 'C.csv', 'D.csv', 'E.csv', 'F.csv']
        csvWriter.writerow(
            ["点", "tx均值", "ty均值", "tz均值", "tx方差", "ty方差", "tz方差", "cx均值", "cy均值", "cz均值", "cx方差", "cy方差", "cz方差",
             "两点距离"])
        for filename in fileList:
            path = os.path.join(folder, filename)
            readAndWritePoint2csv(path, csvWriter)

if __name__ == '__main__':
    main()
    print(u'Memory usage of the current process: %.4f GB' % (psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024 / 1024))
    print("finishing time: ", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

