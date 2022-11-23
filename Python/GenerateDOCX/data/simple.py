from docxtpl import DocxTemplate
import pandas as pd
import os

# zpath = os.getcwd() + '\\'  #获取当前的路径
# zpath = r'E:\python\tj' + '\\'
# file_path = zpath + r'\通知书合集'
# try:
#     os.mkdir(file_path)  #创建一级目录
# except:
#     pass


zpath = os.getcwd() + 'data'  # 获取当前的路径
file_path = zpath = os.getcwd() + 'new'
try:
    os.mkdir(file_path)  # 创建一级目录
except:
    pass

# data = pd.read_csv(zpath + 'data.csv', encoding='gbk')  # 读取csv里的目标数据
data = pd.read_csv('/Users/peiyilin/dev/PyCharm/starlink/data/starlinknewdata.csv', encoding='gbk')
# name = data["姓名"].str.rstrip()  # str.rstrip()用于去掉空白
# academy = data["学院"].str.rstrip()
# major = data["专业"].str.rstrip()
# begin_date = data["开始时间"].str.rstrip()
# end_date = data["结束时间"].str.rstrip()

# time = data["Time"].str.rstrip()
# rerange = data["期号"].str.rstrip()
# number = data["条目编号"].str.rstrip()
# Type = data["Type"].str.rstrip()
# Importance = data["Importance"].str.rstrip()
# Brief = data["Brief"].str.rstrip()
# Content = data["Content"].str.rstrip()
# Publisher = data["Publisher"].str.rstrip()
# SourceUri = data["SourceUri"].str.rstrip()
time = data["Time"]
rerange = data["期号"]
number = data["条目编号"]
Type = data["Type"]
Importance = data["Importance"]
Brief = data["Brief"]
Content = data["Content"]
Publisher = data["Publisher"]
SourceUri = data["SourceUri"]

num = data.shape[0]  # 获取数据行数
for i in range(num):
    context = {
        "Time": time[i],
        "期号": rerange[i],
        "条目编号": number[i],
        "Type": Type[i],
        "Importance": Importance[i],
        "Brief": Brief[i] + "\n",
        "Content": Content[i],
        "Publisher": Publisher[i],
        "SourceUri": SourceUri[i]
    }

    # tpl = DocxTemplate(zpath + '生成文件.docx')
    tpl = DocxTemplate('/Users/peiyilin/dev/PyCharm/starlink/data/template.docx')

tpl.render(context)  # 渲染替换
# 保存文件，名字为： ** 的入学通知书。
# tpl.save(file_path + r"\{}1.docx".format(time[i]))
tpl.save("/Users/peiyilin/dev/PyCharm/starlink/new1.docx".format(time[i]))

print(context)