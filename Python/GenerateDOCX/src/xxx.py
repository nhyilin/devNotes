import numpy as np
from sklearn.cluster import DBSCAN
import matplotlib.pyplot as plt

# 创建数据
data = np.array([[1, 2], [2, 2], [2, 3], [8, 7], [8, 8], [25, 80]])

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
plt.scatter(data[:,0], data[:,1], c=dbscan.labels_, cmap='rainbow')
plt.scatter(cluster_centers[:,0], cluster_centers[:,1], c='black', marker='x')
plt.show()