# 产生特定格式的xml文件，详见代码
# data_file_name中格式如下: 11.2,23.5
def handle(data_file_name, result_file_name):
    # 打开 data.txt 文件，以只读模式
    with open(data_file_name, "r") as data:
        # 打开 result.txt 文件，以写入模式
        with open(result_file_name, "w") as result:
            # 初始化 ID 和 Name 的初始值
            _id = "0_3_"
            _name = "s_num_"
            index = 0
            # 逐行读取 data.txt 中的数据
            for line in data:
                # 去掉每行末尾的换行符
                line = line.strip()
                # 如果不是空行
                if line:
                    # 用空格分割每行的数据，得到经度和纬度
                    longitude, latitude = line.split(",")
                    # 更新 ID 和 Name 的值，按照您的规则递增
                    print(_id + str(index))
                    id = _id + str(index)
                    name = _name + str(index + 1)
                    index = index + 1
                    # 格式化输出结果到 result.txt 中，每一行结果如下：
                    # <GroundStation Latitude="34.8705" Longitude="139.474" Height="0.000000" GroundStationModel="Factory.osgb" GroundStationImage="" Posx="0.000000" Posy="0.000000" Posz="0.000000" Anglex="0.000000" Angley="0.000000" Anglez="0.000000" m_scale="1.000000" Elevation="15.0" ShowType="10" IsVisible="True" R="0.058824" G="1.000000" B="0.000000" A="1.000000" EndTime="15 Aug 2027 00:00:00.000" StartTime="08 Aug 2027 07:00:00.000" ID="0_3_0" Name="s_num_1" />
                    result.write(
                        f'<GroundStation Latitude="{latitude}" Longitude="{longitude}" Height="0.000000" GroundStationModel="Factory.osgb" GroundStationImage="" Posx="0.000000" Posy="0.000000" Posz="0.000000" Anglex="0.000000" Angley="0.000000" Anglez="0.000000" m_scale="1.000000" Elevation="15.0" ShowType="10" IsVisible="True" R="0.058824" G="1.000000" B="0.000000" A="1.000000" EndTime="15 Aug 2027 00:00:00.000" StartTime="08 Aug 2027 07:00:00.000" ID="{id}" Name="{name}" />\n')

                    # id = id[:-1] + str(int(id[-1]) + 1)
                    # name = name[:-1] + str(int(name[-1]) + 1)


def main():
    data_file_name = "/Volumes/yilinSSD/grid_results.txt"
    result_file_name = "/Users/peiyilin/dev/xxxxxx/result.txt"
    handle(data_file_name, result_file_name)


if __name__ == "__main__":
    main()
