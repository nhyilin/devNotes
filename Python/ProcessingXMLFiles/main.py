import xml.etree.ElementTree as ET

# 定义一个对应表，根据你的要求修改
table = {"02": "xxx", "03": "yyy", "04": "zzz"}
tree = ET.parse("file.xml")
root = tree.getroot()


def do_job(name):
    for row in root:
        # 取倒数三个字符
        last_three = row.text[-3:-1]
        # 转为int
        last_three_int = int(last_three)
        # 如果在对应表中，修改第一个字符串
        if last_three in table:
            row[0].text = table[last_three]
        # 打印修改后的行
        print(row.text)
    tree.write("new_file.xml")

if __name__ == '__main__':
    do_job('PyCharm')

