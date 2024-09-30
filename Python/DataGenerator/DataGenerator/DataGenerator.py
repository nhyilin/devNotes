# 数据生成器
import itertools
import pandas as pd
import numpy as np
import tkinter as tk
from tkinter import filedialog, messagebox

# 初始化数据字典
data = {}

# 动态添加数据列
def add_column(column_name):
    if column_name not in data:
        data[column_name] = []

# 动态添加数据
def add_data(column_name, value):
    if column_name in data:
        data[column_name].append(value)
    else:
        print(f"Column '{column_name}' does not exist.")

# 生成数据并保存
def generate_data():
    # 获取所有数据列的名称和参数
    column_names = [entry.get() for entry in column_entries]
    starts = [float(entry.get()) for entry in start_entries]
    ends = [float(entry.get()) for entry in end_entries]
    nums = [int(entry.get()) for entry in num_entries]

    # 生成数据
    conbined_data = [data_process(start, end, num) for start, end, num in zip(starts, ends, nums)]
    all_permutations = list(itertools.product(*conbined_data))
    excel_data = pd.DataFrame(all_permutations)

    # 重命名数据列
    excel_data.rename(columns=dict(zip(range(len(column_names)), column_names)), inplace=True)

    # 保存数据
    try:
        excel_data.to_excel(file_path.get())
        messagebox.showinfo("保存成功", "数据已成功保存到文件夹。")
    except Exception as e:
        messagebox.showerror("保存失败", f"保存数据时出错：{e}")

# 生成数据
def data_process(start, end, num):
    value = np.linspace(start, end, num)
    return value

# 添加数据列
def add_column_entry():
    global row_count
    column_label = tk.Label(root, text="数据列名称:")
    column_label.grid(row=row_count, column=0)
    column_entry = tk.Entry(root)
    column_entry.grid(row=row_count, column=1)
    column_entries.append(column_entry)

    start_label = tk.Label(root, text="起始值:")
    start_label.grid(row=row_count, column=2)
    start_entry = tk.Entry(root)
    start_entry.grid(row=row_count, column=3)
    start_entries.append(start_entry)

    end_label = tk.Label(root, text="结束值:")
    end_label.grid(row=row_count, column=4)
    end_entry = tk.Entry(root)
    end_entry.grid(row=row_count, column=5)
    end_entries.append(end_entry)

    num_label = tk.Label(root, text="取值数:")
    num_label.grid(row=row_count, column=6)
    num_entry = tk.Entry(root)
    num_entry.grid(row=row_count, column=7)
    num_entries.append(num_entry)

    row_count += 1

root = tk.Tk()

# 设置窗口标题
root.title("数据生成器")

column_entries = []
start_entries = []
end_entries = []
num_entries = []
row_count = 0

# 添加初始数据列
add_column_entry()

button = tk.Button(root, text="添加数据列", command=add_column_entry)
button.grid(row=row_count+20, column=0, columnspan=2, sticky="ew")

button = tk.Button(root, text="生成数据并保存", command=generate_data)
button.grid(row=row_count+20, column=2, columnspan=2, sticky="ew")

file_path = tk.StringVar()
file_button = tk.Button(root, text="选择输出文件夹", command=lambda: file_path.set(filedialog.asksaveasfilename(defaultextension=".xlsx")))
file_button.grid(row=row_count+20, column=4, columnspan=2, sticky="ew")

root.mainloop()
