# 导入模块
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 定义 x、y、z 列表
x = [1, 2, 3, 4, 5]
y = [2, 4, 6, 8, 10]
z = [3, 6, 9, 12, 15]

# 创建一个图形对象
fig = plt.figure()

# 创建一个 3D 轴对象
# ax = Axes3D(fig)
ax = fig.add_axes(Axes3D(fig)) # 新代码
# 绘制散点图
ax.scatter(x, y, z)

# 显示图形
plt.show()