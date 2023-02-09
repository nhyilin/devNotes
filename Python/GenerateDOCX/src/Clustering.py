import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from datetime import datetime, timedelta
import matplotlib.dates as mdates
import os
import julian
from collections import Counter

CURRENT_DIR = os.getcwd()
RESULT_FILE = CURRENT_DIR + "/result.csv"


def get_data_from_result(file, col):
    result = []
    with open(file, encoding='gbk') as f:
        render = csv.reader(f)  # reader(迭代器对象)--> 迭代器对象
        for line in render:
            result.append(line[col])
        del result[0]  # 去掉表头项

    if col != 6:
        # 取数据时，忽略对时间的额外处理，对时间的格式化见yyyymmdd_to_jd函数
        for index, value in enumerate(result):
            if value == '':
                result[index] = float(result[index - 1])
            else:
                result[index] = float(value)
    return result


def yyyymmdd_to_jd(date, anchor):
    if date != '':
        date = datetime.strptime(date, '%Y%m%d')
        a = (14 - date.month) // 12
        y = date.year + 4800 - a
        m = date.month + 12 * a - 3
        jd = date.day + (153 * m + 2) // 5 + 365 * y + y // 4 - y // 100 + y // 400 - 32045
        return jd
    else:
        return anchor


def yyyymmdd_to_date_time(date, anchor):
    if date != '':
        return datetime.strptime(date, '%Y%m%d')
    else:
        return str(anchor)


def jd_to_xtime(jd_list):
    result = []
    for i in jd_list:
        i = int(i)
    result.append([datetime.strptime(str(int(jd)), "%j") for jd in jd_list])

    # 绘制图表
    # fig, ax = plt.subplots()
    # ax.plot(dates, [1, 2, 3, 4, 5])
    #
    # # 设置 X 轴的标签格式
    # ax.xaxis.set_major_formatter(mdates.DateFormatter("%Y%m%d"))
    # fig.autofmt_xdate()
    #
    # # 显示图表
    # plt.show()

    return result


def zip_data(data1, data2):
    # 将[1, 2, 3]、[6, 7, 8]转换为[[1, 6], [2, 7], [3, 8]]
    merged_list = list(zip(data1, data2))
    result = [[x, y] for x, y in merged_list]
    return result


def count_points_in_label(labels):
    return Counter(labels)


def remove_problematic_values(data_list):
    # 计算数据的平均数
    mean = np.mean(data_list)

    # 计算数据的标准差
    std = np.std(data_list)

    # 设置阈值
    threshold = 2

    # 计算每个数据点的 Z-Score
    z_scores = [(x - mean) / std for x in data_list]

    # 对超过阈值的数据点赋值为平均值
    for i, z_score in enumerate(z_scores):
        if abs(z_score) > threshold:
            data_list[i] = mean


def one_degree(isSavePic, needDrawPic, logCenter):
    data_list = []

    with open(RESULT_FILE, encoding='gbk') as f:
        render = csv.reader(f)  # reader(迭代器对象)--> 迭代器对象
        for line in render:
            if line[9] == '轨道高度':
                continue
            elif line[9] == '':
                continue
            else:
                data_list.append(float(line[9]))

    # 样本数据（单列）
    data = np.array(data_list).reshape(-1, 1)

    # 聚类数量
    kmeans = KMeans(n_clusters=7)

    # 输入数据拟合
    kmeans = kmeans.fit(data)

    # 基于数据获取质心和标签的值
    centroids = kmeans.cluster_centers_
    labels = kmeans.labels_

    # 统计某一类的数据个数
    unique, counts = np.unique(labels, return_counts=True)
    count_dict = dict(zip(unique, counts))
    print(count_dict)

    if logCenter:
        print("质心：\n", centroids)
        print("标签：\n", labels)

    if needDrawPic:
        fig, ax = plt.subplots(dpi=600)
        now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        plt.title("Plot generated at " + now)
        ax.scatter(data[:, 0], np.random.rand(len(data)), c=labels)
        # ax.scatter(centroids[:, 0], np.mean(data), marker="x", s=200, linewidths=3, color='r')
        plt.show()
        if isSavePic:
            fig.savefig("single_dim.pdf", format='pdf')


def double_degree(isSavePic, needDrawPic, logCenter):
    start_list = get_data_from_result(RESULT_FILE, 5)
    x_time = []
    temp_anchor = 0  # 此变量是为防止数据list里有空值，空值本身无意义，故将其赋值为上一个点的值
    for index, value in enumerate(start_list):
        temp = yyyymmdd_to_jd(str(int(value)), temp_anchor)
        temp_anchor = temp
        start_list[index] = float(temp)
        height_list = get_data_from_result(RESULT_FILE, 9)
        if value != '':
            x_time.append(str(int(value)))
        else:
            x_time.append(str(start_list[index - 1]))

    # 根据Z-Score算法排除噪音,其中噪音点另起为均值
    remove_problematic_values(height_list)
    remove_problematic_values(start_list)

    # 将日期和start_time拼接为[[,],[,],[,]]形式，为聚类准备
    zippd_data = np.array(zip_data(start_list, height_list))

    # 创建 KMeans 模型并训练
    kmeans = KMeans(n_clusters=5, random_state=0).fit(zippd_data)

    # 获取分类结果与中心质心
    labels = kmeans.labels_

    print(count_points_in_label(labels))

    cluster_centers = kmeans.cluster_centers_

    # 统计某一类的数据个数
    unique, counts = np.unique(labels, return_counts=True)
    count_dict = dict(zip(unique, counts))

    cluster_centers = np.around(cluster_centers, decimals=2)

    if logCenter:
        print("质心：\n", cluster_centers)
        print("标签：\n", labels)

    if needDrawPic:
        # 绘制结果图
        now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        fig, ax = plt.subplots(dpi=600)

        # x_normal_time = [datetime.strptime(d, '%Y%m%d') for d in x_time]
        x_normal_time = []
        for d in x_time:
            d = datetime.strptime(d, '%Y%m%d')
            x_normal_time.append(d)

        ax.scatter(x_normal_time, zippd_data[:, 1], c=labels)

        # print(x_normal_time)

        x_cluster_centers = []
        # 将datetime对象格式化为yyyymmdd字符串
        for d in cluster_centers[:, 0]:
            timestamp = (d - 2451545) * 86400
            dt = datetime.fromtimestamp(timestamp)

            # yyyymmdd_str = dt.strftime( "%Y%m%d")
            x_cluster_centers.append(dt)

        # print(x_cluster_centers)

        # ax.scatter(x_cluster_centers, cluster_centers[:, 1], marker='D', s=100, linewidths=3, color='r')
        plt.title("Plot generated at " + now)
        ax.set_xlabel("Time")
        ax.set_ylabel("Height")
        ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
        plt.gcf().autofmt_xdate()
        if isSavePic:
            fig.savefig("double_dim.pdf", format='pdf')

        plt.show()


def main():
    isSavePic = False  # 设置是否将图片保存到本地
    needDrawPic = False  # 测试过程中是否需要绘图
    logCenter = True  # 测试过程中是否需要打印中心点

    # one_degree(isSavePic, needDrawPic, logCenter)
    double_degree(isSavePic, needDrawPic, logCenter)


if __name__ == "__main__":
    main()
