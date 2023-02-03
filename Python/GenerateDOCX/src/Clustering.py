import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from datetime import datetime
import matplotlib.dates as mdates
import os

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


def zip_data(data1, data2):
    # 将[1, 2, 3]、[6, 7, 8]转换为[[1, 6], [2, 7], [3, 8]]
    merged_list = list(zip(data1, data2))
    result = [[x, y] for x, y in merged_list]
    return result


def one_degree(isSavePic):
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
    # print(data_list)
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

    print("质心：\n", centroids)
    print("标签：\n", labels)

    # Plot the data points and centroids
    # plt.figure(dpi=600)
    # # 绘制结果图
    # now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    # plt.title("Plot generated at " + now)
    # plt.scatter(data[:, 0], np.random.rand(len(data)), c=labels)
    # # plt.scatter(centroids[:, 0], np.mean(data), marker="x", s=200, linewidths=3, color='r')
    # plt.show()
    # plt.savefig("single_dim.pdf", format='pdf')

    fig, ax = plt.subplots(dpi=600)
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    plt.title("Plot generated at " + now)
    ax.scatter(data[:, 0], np.random.rand(len(data)), c=labels)
    ax.scatter(centroids[:, 0], np.mean(data), marker="x", s=200, linewidths=3, color='r')
    plt.show()
    if isSavePic:
        fig.savefig("single_dim.pdf", format='pdf')


def double_degree(isSavePic):
    start_list = get_data_from_result(RESULT_FILE, 6)
    temp_anchor = 0  # 此变量是为防止数据list里有空值，空值本身无意义，故将其赋值为上一个点的值
    for index, value in enumerate(start_list):
        temp = yyyymmdd_to_jd(value, temp_anchor)
        temp_anchor = temp
        start_list[index] = float(temp)
        height_list = get_data_from_result(RESULT_FILE, 9)

    # 将日期和start_time拼接为[[,],[,],[,]]形式，为聚类准备
    data = np.array(zip_data(start_list, height_list))

    # 创建 KMeans 模型并训练
    kmeans = KMeans(n_clusters=5, random_state=0).fit(data)

    # 获取分类结果与中心质心
    labels = kmeans.labels_
    cluster_centers = kmeans.cluster_centers_

    # 统计某一类的数据个数
    unique, counts = np.unique(labels, return_counts=True)
    count_dict = dict(zip(unique, counts))

    print(count_dict)

    cluster_centers = np.around(cluster_centers, decimals=2)
    print("质心：\n", cluster_centers)
    print("标签：\n", labels)

    # 绘制结果图
    # 控制横轴为时间格式
    min_start_time = min(start_list)
    max_start_time = max(start_list)

    # date1 = datetime(int(min_start_time[0:3]), int(min_start_time[4:5]), int(min_start_time[5:6]))
    # date2 = datetime(max_start_time[0:3], max_start_time[4:5], max_start_time[5:6])
    # delta = datetime.timedelta(days=1)
    # dates = mdates.drange(date1, date2, delta)

    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    fig, ax = plt.subplots(dpi=600)

    ax.scatter(data[:, 0], data[:, 1], c=labels)
    print(data[:, 0])
    print('\n')
    print(data[:, 1])
    ax.scatter(cluster_centers[:, 0], cluster_centers[:, 1], marker='D', s=100, linewidths=3, color='r')
    plt.title("Plot generated at " + now)
    ax.set_xlabel("Time")
    ax.set_ylabel("Height")
    # ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
    # plt.gcf().autofmt_xdate()
    if isSavePic:
        fig.savefig("double_dim.pdf", format='pdf')

    plt.show()


def main():
    isSavePic = False  # 设置是否将图片保存到本地
    # one_degree(isSavePic)
    double_degree(isSavePic)


if __name__ == "__main__":
    main()
