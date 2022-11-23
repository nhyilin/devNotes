from docxtpl import DocxTemplate
import pandas as pd
import csv
import os

CURRENT_DIR = os.getcwd()  # 获取当前的路径
TIME = 0
RERANGER = 1
NUMBER = 2
TYPE = 3
IMPORTANCE = 4
BRIEF = 5
CONTENT = 6
PUBLISHER = 7
SOURCEURI = 8
TEMPFILE = "情报要报.docx"


def mkdir(path):
    path = path.strip()
    path = path.rstrip("/")
    isExists = os.path.exists(path)
    if not isExists:
        os.makedirs(path.encode('utf-8'))
        print(path + ' 创建成功')
        return path
    else:
        print(path + ' 目录已存在')
        return path


def list_dir(path, list_name):
    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        if os.path.isdir(file_path):  # 判断是否目录
            list_dir(file_path, list_name)
        else:
            list_name.append(file_path)


def list_csv(file_dir):
    list = []
    dir_list = os.listdir(file_dir)
    for cur_file in dir_list:
        path = os.path.join(file_dir, cur_file)
        if os.path.isfile(path):
            dir_files = os.path.join(file_dir, cur_file)
        if os.path.splitext(path)[1] == '.csv':
            csv_file = os.path.join(file_dir, cur_file)
            list.append(csv_file)
        if os.path.isdir(path):
            list_dir(path)
    return list


def makeDic(key, value):
    dic = {key: value}
    return dic


def process_single_CSV_file(csvfile):
    global NEW_FILE_PATH
    NEW_FILE_PATH = mkdir(CURRENT_DIR + '/new')
    global CSV_PATH
    CSV_PATH = mkdir(CURRENT_DIR + '/data')
    global time
    data = pd.read_csv(csvfile, encoding='gbk')
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

    global Brief_dic
    Brief_data = str()
    for i in range(num):
        Brief_data += str(number[i])
        Brief_data += ' '
        Brief_data += Brief[i]
        Brief_data += '\n'
    Brief_dic = makeDic("Brief", Brief_data)
    print("Brief_data: ", '\n', Brief_dic)

    global Content_dic
    Content_data = str()
    for i in range(num):
        Content_data += str(number[i])
        Content_data += ' '
        Content_data += Content[i]
        Content_data += '\n'
    Content_dic = makeDic("Content", Content_data)
    print("Content_dic: ", '\n', Content_dic)


def main():
    process_single_CSV_file("/Users/peiyilin/dev/devNotes/Python/GenerateDOCX/data/20221118-第XXX期.csv")
    # tpl = DocxTemplate(CSV_PATH + TEMPFILE)
    tpl = DocxTemplate("/Users/peiyilin/dev/devNotes/Python/GenerateDOCX/data/情报要报.docx")
    tpl.render(Content_dic)  # 渲染替换
    # 保存文件，名字为： ** 的入学通知书。
    # tpl.save(file_path + r"\{}1.docx".format(time[i]))
    tpl.save(NEW_FILE_PATH + r"\{}.docx".format(time[0]))


# # data = pd.read_csv(zpath + 'data.csv', encoding='gbk')  # 读取csv里的目标数据
# data = pd.read_csv(CSV_PATH + '*.csv', encoding='gbk')
#
# time = data["Time"].str.rstrip()
# rerange = data["期号"].str.rstrip()
# number = data["条目编号"].str.rstrip()
# Type = data["Type"].str.rstrip()
# Importance = data["Importance"].str.rstrip()
# Brief = data["Brief"].str.rstrip()
# Content = data["Content"].str.rstrip()
# Publisher = data["Publisher"].str.rstrip()
# SourceUri = data["SourceUri"].str.rstrip()
#
# num = data.shape[0]  # 获取数据行数
# for i in range(num):
#     context = {
#         "Time": time[i],
#         "期号": rerange[i],
#         "条目编号": number[i],
#         "Type": Type[i],
#         "Importance": Importance[i],
#         "Brief": Brief[i] + "\n",
#         "Content": Content[i],
#         "Publisher": Publisher[i],
#         "SourceUri": SourceUri[i]
#     }
#
# # tpl = DocxTemplate(zpath + '生成文件.docx')
# tpl = DocxTemplate(CSV_PATH + '*.docx')
#
# tpl.render(context)  # 渲染替换
# # 保存文件，名字为： ** 的入学通知书。
# # tpl.save(file_path + r"\{}1.docx".format(time[i]))
# tpl.save(NEW_FILE_PATH + r"\{}.docx".format(time[i]))

if __name__ == "__main__":
    main()
