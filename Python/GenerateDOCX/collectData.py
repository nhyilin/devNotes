# -*- coding : utf-8-*-
import os

import pandas as pd
import csv
from datetime import datetime, timedelta

WORKDING_DIR = 'D:/STLK_DATA/230129-内容待完成/'
SMALL_FILE = WORKDING_DIR + '总44235-54873-调整.csv'
# SMALL_FILE = WORKDING_DIR + '测试用例.csv'
HEIGHT_DIC = WORKDING_DIR + 'ods_result_date.csv'


def read_small_csv_2_memory_pandas():
    global df
    df = pd.read_csv(SMALL_FILE, encoding='gbk')

    filtered_df = df[(df.iloc[:, 7] == 'C') | (df.iloc[:, 7] == 'G')]
    global row_index
    row_index = df.index
    next_row = filtered_df.shift(-1)
    global result_df
    result_df = pd.concat([filtered_df, next_row], axis=0)


def cal_date(date1, date2):
    date1 = datetime.strptime(date1, '%Y%m%d')
    date2 = datetime.strptime(date2, '%Y%m%d')
    time_delta = date1 - date2
    return time_delta.days


# def reformat_csv():

def search_for_height(height_file, SatID, StartTime, EndTime):
    # 为数据平稳准确，暂不使用StartTime作为搜寻高度的因素
    for line in height_file:
        if line[0] == SatID and line[15] == EndTime:
            dic_height = line[2]
            return dic_height


def search_for_intlid(SatID):
    for line in height_file:
        if line[0] == SatID:
            intlid = line[1]
            return intlid


def read_small_csv_2_memory_csv():
    """
    读取总44235-54873-调整.csv文件，并在其中计算时间差，
    将其结果打印到"D:\resulu.csv"中，
    其中所有表格皆为全局变量，方便其他函数使用
    """
    global small_file
    global index_small_file
    global cost_time
    global end_time
    global height_file
    small_file = []
    index_small_file = []
    cost_time = []
    end_time = []
    height_file = []

    with open(HEIGHT_DIC, 'r') as csv_file:
        # 打开查高度的文件
        csv_reader = csv.reader(csv_file)
        for line in csv_reader:
            height_file.append(line)

    with open(SMALL_FILE, 'r') as csv_file:
        csv_reader = csv.reader(csv_file)

        for line in csv_reader:
            small_file.append(line)

        for index, value in enumerate(small_file):
            if (value[7] == 'C') | (value[7] == 'G'):
                index_small_file.append(index)

        with open('D:/result.csv', 'w', newline='') as f:
            header = ['序号', '卫星NORAD', '卫星intlid', '卫星名称', '发射时间', '开始时间', '结束时间',
                      '持续时长', '阶段标定', '轨道高度']
            writer = csv.writer(f)
            writer.writerow(header)
            num = 0
            for i in index_small_file:
                if small_file[i + 1][1] != '' and small_file[i][1] != '' and small_file[i][0] == small_file[i + 1][0]:
                    sat_state = small_file[i][7]
                    small_file[i][8] = sat_state

                    cost_time = cal_date(small_file[i + 1][1], small_file[i][1])
                    small_file[i][7] = str(cost_time)

                    end_time = small_file[i + 1][1]
                    small_file[i][6] = end_time

                    start_time = small_file[i][1]
                    small_file[i][5] = start_time

                    sat_id = small_file[i][0]
                    small_file[i][1] = sat_id

                    height = search_for_height(height_file, sat_id, start_time, end_time)
                    small_file[i][9] = height

                    intlid = search_for_intlid(sat_id)
                    small_file[i][2] = intlid

                    small_file[i][0] = ''  # 第一列为空

                    writer.writerow(small_file[i])
                    num = num + 1
                elif small_file[i + 1][1] == '' and small_file[i][1] != '':
                    sat_state = small_file[i][7]
                    small_file[i][8] = sat_state

                    cost_time = '已有数据中尚无法观测'
                    small_file[i][7] = cost_time

                    end_time = small_file[i + 1][1]
                    small_file[i][6] = end_time

                    start_time = small_file[i][1]
                    small_file[i][5] = start_time

                    sat_id = small_file[i][0]
                    small_file[i][1] = sat_id

                    height = search_for_height(height_file, sat_id, start_time, end_time)
                    small_file[i][9] = height

                    intlid = search_for_intlid(sat_id)
                    small_file[i][2] = intlid

                    small_file[i][0] = ''  # 第一列、第九列为空

                    writer.writerow(small_file[i])
                    num = num + 1

                percentage = round(num / 3930, 3) * 100
                # percentage = round(num / 1072, 3) * 100
                # print(num)
                print(str(percentage)[0:4] + '%')


def main():
    read_small_csv_2_memory_csv()
    print("hello world!")


if __name__ == "__main__":
    main()
