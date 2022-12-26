from win32com.client import Dispatch
from os import walk
import win32com

word = win32com.client.Dispatch('Word.Application')


def doc2pdf(input_file):
    doc = word.Documents.Open(input_file)
    if file.endswith(".doc"):  # word文件后缀名有.doc和.docx
        doc.SaveAs(input_file.replace(".doc", ".pdf"), FileFormat=17)
    elif file.endswith(".docx"):
        doc.SaveAs(input_file.replace(".docx", ".pdf"), FileFormat=17)
    doc.Close()


if __name__ == "__main__":
    directory = "C:/dev/GenerateDOCX/new"  # 绝对路径
    for root, dirs, filenames in walk(directory):
        for file in filenames:
            if file.endswith(".doc") or file.endswith(".docx"):
                print("processing " + file)
                doc2pdf(str(root + "\\" + file))
    word.Quit()
