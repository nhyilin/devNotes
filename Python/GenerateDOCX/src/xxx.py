import pandas as pd
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# 读取数据
data = pd.read_csv("../data.csv", encoding="utf8")

# 将日期列转化为整数
data["date"] = pd.to_datetime(data["date"], format='%Y%m%d')
data["date"] = data["date"].astype(int) / 10**9
print(data["date"])
# 创建KMeans模型并训练
kmeans = KMeans(n_clusters=3)
kmeans.fit(data.iloc[:, :-1])

# 获取中心质心
centroids = kmeans.cluster_centers_

# 绘制结果
plt.scatter(data["date"], data["value"], c=kmeans.labels_)
# plt.scatter(centroids[:, 0], centroids[:, 1], marker='x', s=200, linewidths=3, color='r')
plt.show()
