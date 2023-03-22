import re
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def main():
    # 打开文件
    file = open("data/2023-03-20_1.log", encoding="utf-8", mode="r")

    # 定义一个列表，用于存储 B、L、H 的数据
    _b = []
    _l = []
    _h = []

    # 逐行读取文件
    for line in file:
        # 按空格分隔字符串
        words = line.split()
        # 获取 blh.B、blh.L、blh.H 的数据
        b = words[-3].split(":")[1]
        l = words[-2].split(":")[1]
        h = words[-1].split(":")[1]
        # 将数据转换为浮点数，并存入列表
        _b.append(float(b))
        _l.append(float(l))
        _h.append(float(h))

    # 关闭文件
    file.close()

    # 打印列表
    print(_b)
    print(_l)
    print(_h)

    # 创建一个图形对象
    fig = plt.figure()

    # 创建一个 3D 轴对象
    # ax = Axes3D(fig)
    ax = fig.add_axes(Axes3D(fig))  # 新代码

    ax.scatter(_b, _l, _h)
    plt.show()


if __name__ == '__main__':
    main()
