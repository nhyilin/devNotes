import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import numpy as np
import datetime

# 创建数据
date1 = datetime.datetime(2021, 1, 1)
date2 = datetime.datetime(2022, 1, 1)
delta = datetime.timedelta(days=5)
dates = mdates.drange(date1, date2, delta)
y = np.sin(dates)

# 绘图
fig, ax = plt.subplots()
ax.plot(dates, y)

# 设置x轴的数据格式
ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
plt.gcf().autofmt_xdate()

plt.show()
