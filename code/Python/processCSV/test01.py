import os
import csv
import vtk
import psutil
import datetime
import numpy as np

COLS_BASE = 9
COLS_QUATERNION = 34
COLS_BIAS = 38
POINTCOLS = 3
QUATERNION = 4
SHARP_X_INDEX_IN_ARRANGEMENT = 6
BASE_X_INDEX_IN_ARRANGEMENT = 0
TIP_TO_CENTER_ON_SHARPPROBE= [0, -121, 0]
WRITE_PATH = "E:/tmc/vtk_development/goldFinger/test01/refactor08.csv"
FOLDER = "E:\\tmc\\vtk_development\\goldFinger\\1"
FILE_LIST = ['A.csv', 'B.csv', 'C.csv', 'D.csv', 'E.csv', 'F.csv']

img_path = FOLDER

fileList = sorted(os.listdir(img_path))  # 文件名按字母排序

print(fileList)