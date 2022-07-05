from itertools import groupby
import xlrd


def linear_filter(score_list):
    step = 0.01
    for k, g in groupby(sorted(score_list), key=lambda x: x // step):
        print('{}-{}: {}'.format(k * step, (k + 0.01) * step + 0.01, len(list(g))))


def read_xlrd():
    global cols
    worksheet = xlrd.open_workbook('./data.xlsx')
    sheet_names = worksheet.sheet_names()
    # print(sheet_names)
    for sheet_name in sheet_names:
        sheet = worksheet.sheet_by_name(sheet_name)

        cols = sheet.col_values(3)
        del cols[0]
        # print(type(cols[3]))  # 查看数据类型
        # print(type(cols))  # 查看数据类型
    return cols


if __name__ == '__main__':
    linear_filter(read_xlrd())
