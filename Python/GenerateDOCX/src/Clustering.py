# -*- coding : utf-8-*-
import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from datetime import datetime, timedelta
import matplotlib.dates as mdates
import os
import julian
from collections import Counter
from astropy.time import Time
from sklearn.mixture import GaussianMixture
import pandas as pd
import matplotlib
import random
from sklearn.cluster import DBSCAN
from matplotlib.pyplot import MultipleLocator

CURRENT_DIR = os.getcwd()
RESULT_FILE = CURRENT_DIR + "/../data/result.csv"


def get_data_from_result(file, col):
    # 返回值为成员为float类型的list
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


def screening_the_same_batch_of_satellites(input_list, sat_batch):
    result = []
    for ele in input_list:
        if sat_batch == "ele":
            result.append(ele)
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


# def yyyymmdd_to_date_time(date, anchor):
#     if date != '':
#         return datetime.strptime(date, '%Y%m%d')
#     else:
#         return str(anchor)


def jd_to_xtime(jd_list):
    # 将包含儒略日的列表对象格式化为yyyymmdd字符串的列表
    result = []
    for jd in jd_list:
        t = Time(jd, format='jd')
        t = t.strftime("%Y-%m-%d")
        result.append(t)
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
    return data_list


def alg_kmeans(data_list1, data_list2):
    # 对传入数据进行Z-Score去除噪声
    remove_problematic_values(data_list1)
    remove_problematic_values(data_list2)

    # 将日期和start_time拼接为[[,],[,],[,]]形式，为聚类准备
    zippd_data_with_jd_time = np.array(zip_data(data_list1, data_list2))
    # 创建 KMeans 模型并训练
    kmeans = KMeans(n_clusters=4, random_state=0, n_init=10).fit(zippd_data_with_jd_time)
    # 获取分类结果与中心质心
    labels = kmeans.labels_
    print(count_points_in_label(labels))
    cluster_centers = kmeans.cluster_centers_
    # 统计某一类的数据个数
    unique, counts = np.unique(labels, return_counts=True)
    count_dict = dict(zip(unique, counts))
    cluster_centers = np.around(cluster_centers, decimals=2)
    return cluster_centers, labels, zippd_data_with_jd_time


def alg_gaussianMixture(data, COMPONENTS, ax, needDrawPic):
    gmm = GaussianMixture(n_components=COMPONENTS)
    gmm.fit(data)

    # predictions from gmm
    labels = gmm.predict(data)
    frame = pd.DataFrame(data)
    frame['cluster'] = labels
    frame.columns = ['Time', 'Height', 'cluster']
    num_colors = int(COMPONENTS)
    colors = []
    for i in range(num_colors):
        red = random.randint(0, 255)
        green = random.randint(0, 255)
        blue = random.randint(0, 255)
        color = f"#{red:02x}{green:02x}{blue:02x}"
        colors.append(color)

    # colors = ['blue', 'green', 'cyan', 'black']  # 这里颜色个数应随COMPONENTS个数来动态变化
    for k in range(0, COMPONENTS):
        data = frame[frame["cluster"] == k]
        data_x = [int(ele) for ele in data["Time"]]
        data_x = [str(ele) for ele in data_x]
        data_x = jd_to_xtime(data_x)
        data_x = [datetime.strptime(item, "%Y-%m-%d") for item in data_x]
        # ax.scatter(data["Time"], data["Height"], c=colors[k])
        ax.scatter(data_x, re_handle_y_data(data["Height"]), c=colors[k])
        ax.set_xlabel("Time")
        ax.set_ylabel("Height")
        ax.xaxis.set_major_locator(mdates.AutoDateLocator())
        ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
    center = []
    for i in range(gmm.n_components):
        center.append(gmm.means_[i])
    if needDrawPic:
        plt.show()


def alg_DBSCAN(data):
    data = np.array(data)
    # 运行 DBSCAN 聚类
    dbscan = DBSCAN(eps=3, min_samples=2)
    dbscan.fit(data)

    # 计算所有聚类的中心点
    cluster_centers = []
    for i in np.unique(dbscan.labels_):
        cluster_center = np.mean(data[dbscan.labels_ == i], axis=0)
        cluster_centers.append(cluster_center)
    cluster_centers = np.array(cluster_centers)

    # 绘制 DBSCAN 聚类结果
    plt.scatter(data[:, 0], re_handle_y_data(data[:, 1]), c=dbscan.labels_, cmap='rainbow')
    plt.scatter(cluster_centers[:, 0], re_handle_y_data(cluster_centers[:, 1]), c='black', marker='x')
    plt.show()


def kmeans_scatter_data(ax, data_x, data_y, marker_type, marker_size, _linewidth, _color, whether_show_plt, isSavePic):
    """
    kmeans聚类时，绘图抽取出来的函数
    ax：绘图
    data_x：x轴数据
    data_y：y轴数据
    marker_type：绘图marker样式参数
    marker_size：绘图marker大小参数
    _linewidth：绘图线宽参数
    _color：绘图颜色参数
    whether_hold_on：若在某个图形或某坐标轴上重复调用此函数，多次绘制，则前几次需要该参数为False，最后一次绘制需要另其为True，起到Hold on的效果
    isSavePic：是否需要保存图片
    """

    data_x = [datetime.strptime(item, "%Y-%m-%d") for item in data_x]
    data_y = re_handle_y_data(data_y)
    ax.scatter(data_x, data_y, marker=marker_type, s=marker_size, linewidths=_linewidth, c=_color)

    # --------这里是突出显示某一时间
    ax.axvline(datetime.strptime("2021-05-16", "%Y-%m-%d"), color='blue', linestyle='--')
    ax.axvline(datetime.strptime("2021-06-24", "%Y-%m-%d"), color='blue', linestyle='--')
    ax.axvline(datetime.strptime("2021-07-01", "%Y-%m-%d"), color='red', linestyle='--')

    ax.axhline(382, color='purple', linestyle='--')
    ax.annotate("382 km", xy=(0, 382), xytext=(0, 382), arrowprops=dict(facecolor='purple', shrink=0.05), )

    ax.axvline(datetime.strptime("2021-10-21", "%Y-%m-%d"), color='red', linestyle='--')
    # Annotate the line
    ax.annotate("Starlink-1095 sustained orbital altitude 382 km",
                xy=(datetime.strptime("2021-05-16", "%Y-%m-%d"), ax.get_ylim()[1]), xycoords='data',
                xytext=(-250, 10), textcoords='offset points',
                arrowprops=dict(facecolor='blue', arrowstyle="->",
                                connectionstyle="arc3,rad=-0.2"),
                color='blue', fontsize=12)

    ax.annotate("Chinese space station adjusts orbit",
                xy=(datetime.strptime("2021-07-01", "%Y-%m-%d"), ax.get_ylim()[1]), xycoords='data',
                xytext=(100, 30), textcoords='offset points',
                arrowprops=dict(facecolor='red', arrowstyle="->",
                                connectionstyle="arc3,rad=-0.2"),
                color='red', fontsize=12)

    ax.annotate("Chinese space station adjusts orbit secondly",
                xy=(datetime.strptime("2021-10-21", "%Y-%m-%d"), ax.get_ylim()[0]), xycoords='data',
                xytext=(100, 30), textcoords='offset points',
                arrowprops=dict(facecolor='red', arrowstyle="->",
                                connectionstyle="arc3,rad=-0.2"),
                color='red', fontsize=12)

    ax.set_xlabel("Time")
    ax.set_ylabel("Height")
    # ax.xaxis.set_major_locator(mdates.AutoDateLocator())
    ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
    plt.gca().xaxis.set_major_locator(mdates.MonthLocator())
    plt.gcf().autofmt_xdate()
    if whether_show_plt:
        plt.grid()
        plt.show()

    if isSavePic:
        fig.savefig("double_dim.pdf", format='pdf')


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

    data = np.array(data_list).reshape(-1, 1)  # 样本数据（单列）
    kmeans = KMeans(n_clusters=7, n_init=10)  # 聚类数量
    kmeans = kmeans.fit(data)  # 输入数据拟合
    centroids = kmeans.cluster_centers_  # 基于数据获取质心和标签的值
    labels = kmeans.labels_

    # 统计某一类的数据个数
    unique, counts = np.unique(labels, return_counts=True)
    count_dict = dict(zip(unique, counts))
    print(count_dict)

    if logCenter:
        print("质心：\n", centroids)
        print("标签：\n", labels)

    if needDrawPic:
        fig, ax = plt.subplots()
        now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        plt.title("Plot generated at " + now)
        # ax.scatter(data[:, 0], np.random.rand(len(data)), c=labels)
        ax.scatter(np.random.rand(len(data)), data[:, 0], c=labels)
        # ax.scatter(centroids[:, 0], np.mean(data), marker="x", s=200, linewidths=3, color='r')
        plt.show()
        if isSavePic:
            fig.savefig("single_dim.pdf", format='pdf')


def handle_y_data(input_list):
    output_list = [ele * 999999999999999999 for ele in input_list]
    return output_list


def re_handle_y_data(input_list):
    output_list = [ele * 1 / 999999999999999999 for ele in input_list]
    return output_list


def get_file_double_degree(pattern):
    """
    数据清洗，若采取清洗模式，则参数为CLEAN，若采取均值模式，则参数为MIX
    """
    start_list_in_csv = get_data_from_result(RESULT_FILE, 5)  # 此时还是float对象组成的list
    height_list_in_csv = []

    start_list = []
    height_list = []
    if pattern == 'CLEAN':
        for index, value in enumerate(start_list_in_csv):
            if value != '':
                start_list.append(start_list_in_csv[index])
    elif pattern == 'MIX':
        temp_anchor = 0  # 此变量是为防止数据list里有空值，空值本身无意义，故将其赋值为上一个点的值
        for index, value in enumerate(start_list_in_csv):
            temp = yyyymmdd_to_jd(str(int(value)), temp_anchor)
            temp_anchor = temp
            start_list_in_csv[index] = float(temp)
            height_list_in_csv = get_data_from_result(RESULT_FILE, 9)
    else:
        print("数据清洗模式参数输入错误")

    return height_list_in_csv, start_list_in_csv


def double_degree(isSavePic, needDrawPic, logCenter):
    # 数据清洗，若采取清洗模式，则参数为CLEAN，若采取均值模式，则参数为MIX
    height_list, start_list = get_file_double_degree('MIX')

    global fig
    # fig, (ax_kmeans, ax_gaussian) = plt.subplots(1, 2)
    fig, ax_kmeans = plt.subplots()

    # -------------------------------------------DBSCAN聚类
    # 效果不好，不采用
    # alg_DBSCAN(zip_data(start_list, handle_y_data(height_list)))

    # -------------------------------------------kmeans聚类
    height_list = handle_y_data(height_list)  # 将高度轴放大n倍...这样可以保证特征聚类在高度而非时间
    cluster_centers, labels, zippd_data_with_jd_time = alg_kmeans(start_list, height_list)
    if logCenter:
        print("kmeans质心：\n", cluster_centers)
        # print("kmeans标签：\n", labels)

    if needDrawPic:
        # 绘制结果图
        x_data1 = jd_to_xtime(zippd_data_with_jd_time[:, 0])
        y_data1 = zippd_data_with_jd_time[:, 1]
        x_data2 = jd_to_xtime(cluster_centers[:, 0])
        kmeans_scatter_data(ax_kmeans, x_data1, y_data1, None, None, None, labels, False, isSavePic)
        kmeans_scatter_data(ax_kmeans, x_data2, cluster_centers[:, 1], 'x', None, None, 'r', True, isSavePic)

    # -------------------------------------------GaussianMixture
    return
    COMPONENTS = 6
    df = pd.DataFrame(zippd_data_with_jd_time, columns=['time', 'height'])
    result_x, result_y, gaussian_center_arry = alg_gaussianMixture(df, COMPONENTS, ax_gaussian, needDrawPic)

    return

    gaussian_x = [temp[0] for temp in result_x]
    gaussian_x = jd_to_xtime(gaussian_x)  # 绘图的横轴，时间格式为yymmdd

    gaussian_y = [temp[0] for temp in result_y]

    gaussian_center_x = [temp[0] for temp in gaussian_center_arry]
    gaussian_center_x = jd_to_xtime(gaussian_center_x)

    gaussian_center_y = [temp[1] for temp in gaussian_center_arry]

    if logCenter:
        print("kmeans高斯质心：\n")
        print(zip_data(gaussian_center_x, gaussian_y))
        # print("kmeans标签：\n", labels)

        color = ['blue', 'green', 'cyan', 'black']
        scatter_data(ax_gaussian, gaussian_x, gaussian_y, None, None, None, color, False, isSavePic)
        scatter_data(ax_gaussian, gaussian_center_x, gaussian_center_y, None, None, None, color, True, isSavePic)


def test():
    inlist = [1, 2, 3]
    print(handle_y_data(inlist))


def main():
    isSavePic = False  # 设置是否将图片保存到本地
    needDrawPic = True  # 测试过程中是否需要绘图
    logCenter = True  # 测试过程中是否需要打印中心点

    # test()
    # return

    double_degree(isSavePic, needDrawPic, logCenter)
    # one_degree(isSavePic, needDrawPic, logCenter)


if __name__ == "__main__":
    main()
