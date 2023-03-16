import matplotlib.pyplot as plt
import numpy as np
import xxx

from pylab import mpl

n10 = 144
n30 = 48
n60 = 24

x10 = list(range(0, n10))
x30 = list(range(0, n30))
x60 = list(range(0, n60))


def method_name(x, y, n, txt):
    everage = round(sum(y) / n, 2)
    # plt.subplot(2, 2, 1)
    plt.plot(x, y, label='平均值: ' + str(everage))
    plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
    plt.title("时间间隔" + txt + "分钟")
    plt.xlabel("时间段次数")
    plt.ylabel("过境卫星个数")
    plt.legend()
    plt.show()


def main():
    x = x10
    y = xxx.y10
    method_name(x, y, n10, '10')


if __name__ == main():
    main()
