from docxtpl import DocxTemplate
from docx import Document
import pandas as pd
import docx
import os

CURRENT_DIR = os.getcwd() + '/'  # 获取当前的路径
TEMPFILE = "情报要报.docx"
CSV_PATH = "/Users/peiyilin/dev/devNotes/Python/GenerateDOCX/data/"
NEW_FILE_PATH = "/Users/peiyilin/dev/devNotes/Python/GenerateDOCX/new/"


def mkdir(path):
    path = path.strip()
    isExists = os.path.exists(path)
    if not isExists:
        os.makedirs(path.encode('utf-8'))
        return path
    else:
        return path


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


def list_dir(file_dir):
    list_csv = []
    dir_list = os.listdir(file_dir)
    for cur_file in dir_list:
        path = os.path.join(file_dir, cur_file)
        if os.path.isfile(path):
            dir_files = os.path.join(file_dir, cur_file)
        if os.path.splitext(path)[1] == '.csv':
            csv_file = os.path.join(file_dir, cur_file)
            list_csv.append(csv_file)
        if os.path.isdir(path):
            list_dir(path)
    return list_csv


def makeDic(key, value):
    dic = {key: value}
    return dic


def EmptyDir(filepath):
    # 清空目标文件夹
    del_list = os.listdir(filepath)
    for f in del_list:
        file_path = os.path.join(filepath, f)
        if os.path.isfile(file_path):
            os.remove(file_path)


def ReFormatColumn(data, number, textContent, row, key):
    """
    data：字典中的值，将很多条目合并到一起的目标，入值最好为空字符串
    number：csv文件中内容条数索引
    content：csv文件中的内容，如biref和Content
    row:csv文件行数，以供遍历
    key:csv文件的键
    """
    for i in range(row):
        data += str(number[i])
        data += '. '
        data += ' '
        data += textContent[i]
        data += '\n'
    return makeDic(key, data)


def FormatCSV(csvfile):
    global DIC
    DIC = dict()

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
    Brief_dic = ReFormatColumn(Brief_data, number, Brief, num, "Brief")
    DIC.update(Brief_dic)

    global Content_dic
    Content_data = str()
    Content_dic = ReFormatColumn(Content_data, number, Content, num, "Content")
    DIC.update(Content_dic)

    Time_dic = {"Time": time[0]}
    DIC.update(Time_dic)

    Rerange_dic = {"期号": rerange[0]}
    DIC.update(Rerange_dic)

    End_dic = {"此页无正文": "（此页无正文）"}
    DIC.update(End_dic)
    # print("Final dictionary: ", '\n', DIC)


def delete_paragraph(paragraph):
    # 清除word中多余空行
    p = paragraph._element
    p.getparent().remove(p)
    p._p = p._element = None


def DeleteBlankPages(xxx):
    # 清除word中空白页面
    myDoc = Document(xxx)
    for num, paragraphs in enumerate(myDoc.paragraphs):
        if paragraphs.text == "":
            # print('第{}段是空行段'.format(num))
            paragraphs.clear()  # 清除文字，并不删除段落，run也可以,
            delete_paragraph(paragraphs)


def main():
    EmptyDir(NEW_FILE_PATH)
    csv_list = list_csv(CSV_PATH)
    print("csv_fils: ", '\n', csv_list)
    for index in csv_list:
        FormatCSV(index)
        tpl = DocxTemplate(CURRENT_DIR + TEMPFILE)
        tpl.render(DIC)  # 渲染替换
        tpl.save(NEW_FILE_PATH + r"{}.docx".format(time[0]))
        print("Newly generated files： ", NEW_FILE_PATH + r"{}.docx".format(time[0]))
        DeleteBlankPages(NEW_FILE_PATH + r"{}.docx".format(time[0]))


if __name__ == "__main__":
    main()
