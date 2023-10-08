def deal(filename,new_file):
    # 打开一个新的文件，以写入模式
    with open(new_file, "w") as g:
        # 重新打开原来的文件，以读取模式
        with open(filename, "r") as f:
            # 逐行读取
            for line in f:
                # 找到SatName:的位置
                index = line.find("SatName:")
                # 如果存在，删除之前的字符
                if index != -1:
                    line = line[index + len("SatName: "):]
                # 将TLELine1:替换为换行符
                line = line.replace("TLELine1: ", "\n")
                # 将TLELine2:替换为换行符
                line = line.replace("TLELine2: ", "\n")
                # 写入新的文件
                g.write(line)


def main():
    deal("/Volumes/yilinSSD/2023-09-04_0.log","/Volumes/yilinSSD/new.txt")


if __name__ == '__main__':
    main()
