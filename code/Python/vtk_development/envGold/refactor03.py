import os
import csv
import vtk
import psutil
import datetime
import numpy as np

INDEX_BASE_X = 9
INDEX_QUATERNION_START_ROW = 34
INDEX_BIAS_X = 38

POINT_DIMENSION = 3
QUATERNION_DIMENSION = 4

INDEX_BASE_X_IN_ARRANGEMENT = 0
INDEX_SHARP_X_IN_ARRANGEMENT = 6

TIP_TO_CENTER_ON_SHARPPROBE= [0, -121, 0]

WRITE_PATH = "E:/tmc/vtk_development/goldFinger/test01/refactor08.csv"
CSV_FOLDER = "E:\\tmc\\vtk_development\\goldFinger\\1"

def readFile(path):
    with open(path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        column = [row for row in reader]

        basePoint = readSpecificColumnsFromCSV(INDEX_BASE_X, POINT_DIMENSION, column)
        quaternion = readSpecificColumnsFromCSV(INDEX_QUATERNION_START_ROW,QUATERNION_DIMENSION, column)
        bias = readSpecificColumnsFromCSV(INDEX_BIAS_X, POINT_DIMENSION, column)
        arrangementListOfThreeVector = [basePoint,quaternion,bias]
    return arrangementListOfThreeVector

def readSpecificColumnsFromCSV(coordinatesStartColumn, vectorDimension, completeCSVData):
    data_list = []
    for i in range(vectorDimension):
        for index in range(len(completeCSVData)):
            data_list.append(completeCSVData[index][coordinatesStartColumn])
        coordinatesStartColumn = coordinatesStartColumn + 1
    data_list = np.array(data_list)
    data_list = data_list.reshape(vectorDimension, len(completeCSVData))
    data_list = np.transpose(data_list) # 其实不采取转置操作也可行，后面取数据时只需将原来的取列方式改为取行方式即可
    data_list = data_list.astype(float)
    return data_list

def rotateAndBias(quaternion,bias):
    rotatedVector = []
    for i in range(len(quaternion)):
        rotate = vtk.vtkMath()
        ans = [0, 0, 0]
        rotate.RotateVectorByNormalizedQuaternion(TIP_TO_CENTER_ON_SHARPPROBE, quaternion[i], ans)
        rotatedVector.append(ans)
    rotatedVector = np.array(rotatedVector)
    tipOfSharpProbe = []
    for index in range(len(bias)):
        tipOfSharpProbe.append(bias[index] + rotatedVector[index])
    tipOfSharpProbe = np.array(tipOfSharpProbe)
    return tipOfSharpProbe

def arrangeMeanAndVariance(path):
    pointsList = readFile(path)
    testPoint = pointsList[0]
    quaternion = pointsList[1]
    bias = pointsList[2]

    goldFinger = rotateAndBias(quaternion, bias)
    organizedPrintedData = []
    for index in range(3):
        organizedPrintedData.append(np.mean(testPoint[:, index])) # Use numpy instead of statistic library
    for index in range(3):
        organizedPrintedData.append(np.var(testPoint[:, index]))
    for index in range(3):
        organizedPrintedData.append(np.mean(goldFinger[:, index]))
    for index in range(3):
        organizedPrintedData.append(np.var(goldFinger[:, index]))

    return organizedPrintedData

def calcDistance(sharpPoint,basePoint):
    d_x = sharpPoint[0] - basePoint[0]
    d_y = sharpPoint[1] - basePoint[1]
    d_z = sharpPoint[2] - basePoint[2]
    distance = np.sqrt(d_x ** 2 + d_y ** 2 + d_z ** 2)# Remove the reference math library
    return distance

def writePoint2csv(path,writer):
    pointName = os.path.basename(path)[0]# Remove the reference pathlib library
    writeList = arrangeMeanAndVariance(path)
    sharpPoint = writeList[INDEX_SHARP_X_IN_ARRANGEMENT:INDEX_SHARP_X_IN_ARRANGEMENT+3]
    basePoint = writeList[INDEX_BASE_X_IN_ARRANGEMENT:INDEX_BASE_X_IN_ARRANGEMENT+3]
    distance = calcDistance(sharpPoint,basePoint)

    writeList.insert(0, pointName)
    writeList.append(distance)
    writer.writerow(writeList)


def main():
    writePath = WRITE_PATH
    with open(writePath, 'w', encoding='utf-8-sig', newline="") as csvfile:# write instead of append
        csvWriter = csv.writer(csvfile)
        folder = CSV_FOLDER
        fileList = sorted(os.listdir(CSV_FOLDER)) #File names are sorted alphabetically, Optimized the way files are read sequentially
        csvWriter.writerow(
            ["点", "tx均值", "ty均值", "tz均值", "tx方差", "ty方差", "tz方差", "cx均值", "cy均值", "cz均值", "cx方差", "cy方差", "cz方差",
             "两点距离"])
        for filename in fileList:
            path = os.path.join(folder, filename)
            writePoint2csv(path, csvWriter)

if __name__ == '__main__':
    main()
    print(u'Memory usage:   %.4f GB' % (psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024 / 1024))
    print("finishing time:", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))