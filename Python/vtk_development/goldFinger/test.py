import sys
import time
import csv
import pandas as pd
base_path = sys.path[0] + '\\'+ sys.argv[1]
# print(base_path)
# num = 0
# sum = 0
# read_line = int(sys.argv[2]) + 1


def data_handling():
    content = open(base_path, 'r',encoding='utf-8').readlines()
    count_line = len(open(base_path, 'r',encoding='utf-8').readlines())
    time_local = time.strftime('%Y%m%d%H%M%S',time.localtime(int(time.time())))
    new_file = 'result_'+ time_local + '.csv'
    rows_num = 0
    with open( new_file, 'w+', encoding='utf-8',newline = '') as f:

        csv_write = csv.writer(f)
        for i in range(count_line-1):
            if i == 0:
                index_list = content[0].rstrip('\n').replace('    ','  ').replace('   ',' ').replace('  ',' ').split(' ')
                csv_write.writerow(index_list)
                rows_num += 1
            else:
                row_content = content[i]
                # print(row_content)
                row_content_new = row_content.rstrip('\n').replace('    ','  ').replace('   ',' ').replace('  ',' ').split(' ')
                print(row_content_new)
                # print(type(row_content_new[8]))
                registrationPercent = float(row_content_new[8])
                # print(registrationPercent)
                if registrationPercent >= 85.0:
                    csv_write.writerow(row_content_new)
                    rows_num += 1
    df = pd.read_csv(new_file)
    # print(round(sum(df['coronalAngle']), 6))
    with open(new_file, 'a+', encoding='utf-8', newline='') as f:
        csv_write = csv.writer(f)
        result_line = len(open(new_file, 'r',encoding='utf-8').readlines()) -1
        csv_write.writerow(['avg', round(sum(df['transverseAngle']) / result_line, 6), round(sum(df['forceLineAngle(Z-axis)'])/ result_line,6), round(sum(df['originDistance'])/ result_line,6), round(sum(df['coronalAngle'])/ result_line,6), round(sum(df['verticalAngle'])/ result_line,6),round(sum(df['coronalDeviation'])/ result_line,6),round(sum(df['verticalDeviation'])/ result_line,6),round(sum(df['registrationPercent'])/ result_line,6), round(sum(df['iter'])/ result_line,6), round(sum(df['ModelDist'])/ result_line,6)])
        csv_write.writerow(['stb', round(df['transverseAngle'].std(),6), round(df['forceLineAngle(Z-axis)'].std(),6), round(df['originDistance'].std(),6), round(df['coronalAngle'].std(),6), round(df['verticalAngle'].std(),6), round(df['coronalDeviation'].std(),6),round(df['verticalDeviation'].std(),6),round(df['registrationPercent'].std(),6),round(df['iter'].std(),6), round(df['ModelDist'].std(),6)])




    # print(open(new_file, 'r',encoding='utf-8').readlines())

# print('\n第{}行大于10的数有:{}个\n\n和为：{}\n\n平均数为：{}'.format(read_line, num, sum, sum))



data_handling()



