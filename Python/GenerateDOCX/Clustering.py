import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from datetime import datetime


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


def one_degree():
    filename = "result.csv"
    data_list = []

    with open(filename, encoding='gbk') as f:
        render = csv.reader(f)  # reader(迭代器对象)--> 迭代器对象
        for line in render:
            if line[9] == '轨道高度':
                continue
            elif line[9] == '':
                continue
            else:
                data_list.append(float(line[9]))
    print(data_list)
    # 样本数据（单列）
    data = np.array(data_list).reshape(-1, 1)

    # 聚类数量
    kmeans = KMeans(n_clusters=7)

    # 输入数据拟合
    kmeans = kmeans.fit(data)

    # 基于数据获取质心和标签的值
    centroids = kmeans.cluster_centers_
    labels = kmeans.labels_

    print("质心：\n", centroids)
    print("标签：\n", labels)

    # Plot the data points and centroids
    plt.figure(dpi=600)
    # 绘制结果图
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    plt.title("Plot generated at " + now)
    plt.scatter(data[:, 0], np.random.rand(len(data)), c=labels)
    # plt.scatter(centroids[:, 0], np.mean(data), marker="x", s=200, linewidths=3, color='r')
    plt.show()


def double_degree():
    start_list = get_data_from_result('result.csv', 6)
    temp_anchor = 0
    for index, value in enumerate(start_list):
        temp = yyyymmdd_to_jd(value, temp_anchor)
        temp_anchor = temp
        start_list[index] = float(temp)
        height_list = get_data_from_result('result.csv', 9)
    data = np.array(zip_data(start_list, height_list))

    # 创建 KMeans 模型并训练
    kmeans = KMeans(n_clusters=3, random_state=0).fit(data)

    # 获取分类结果与中心质心
    labels = kmeans.labels_
    cluster_centers = kmeans.cluster_centers_

    cluster_centers = np.around(cluster_centers, decimals=2)
    print("质心：\n", cluster_centers)
    print("标签：\n", labels)

    # 绘制结果图
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    plt.figure(dpi=600)
    plt.scatter(data[:, 0], data[:, 1], c=labels)
    plt.scatter(cluster_centers[:, 0], cluster_centers[:, 1], marker='D', s=100, linewidths=3, color='r')
    plt.title("Plot generated at " + now)
    plt.xlabel("Time (Julius Day format)")
    plt.ylabel("Height")
    plt.show()


def main():
    one_degree()
    # double_degree()


if __name__ == "__main__":
    main()
