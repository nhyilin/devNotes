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
#----------pubFunctions-------#


df = pd.read_csv('./IP2LOCATION.csv',encoding= 'utf-8',header=None)
print(type(df))

cols_data_5 = df.iloc[:,0:4]    # 指定连续列，用数字
print(cols_data_5)



print("finishing time: ", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

