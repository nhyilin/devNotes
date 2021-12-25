# -*- coding: utf-8 -*-
"""
批量编码转换，用于批量转换文件的编码，支持utf-8,utf-8-bom,gb2312,gbk编码之间的转化，其他编码暂时没有测试
    src_dir = "../" -->  指定要转换的文件夹路径，支持当前路径
    tag_type = "utf-8-sig" --> 指定目标转换格式
    type_filter = [".cpp", ".h"] --> 指定需要转换的文件类型
注意：utf-8-bom请写成utf-8-sig
"""

import os
import codecs
import chardet


def utf8_conversion(f_context, code_type):
    if code_type.lower() == "utf-8":
        return f_context
    elif code_type.lower() == "utf-8-bom" or code_type.lower() == "utf-8-sig":
        return codecs.BOM_UTF8 + f_context
    else:
        return f_context.decode("utf-8").encode(code_type)


def conversion_to_utf8(f_context, code_type):
    if code_type.lower() == "utf-8":
        return f_context
    elif code_type.lower() == "utf-8-bom" or code_type.lower() == "utf-8-sig":
        return f_context[3:]
    else:
        return f_context.decode(code_type).encode("utf-8")


def file_code_conversion(file_name, tag_code_type):
    src_file = open(file_name, "rb")
    file_context = src_file.read()
    src_file.close()

    if file_context == "":
        print (file_name + "  --  empty file")
        return

    code_type = chardet.detect(file_context)["encoding"]
    if code_type.lower() == tag_code_type.lower():
        print (file_name + "  --  escape file")
        return
    else:
        print (file_name + ("  --  converted from %s into %s" % (code_type, tag_code_type)))
        tag_utf8_context = conversion_to_utf8(file_context, code_type)
        tag_context = utf8_conversion(tag_utf8_context, tag_code_type)
        tag_file = open(file_name, "wb")
        tag_file.write(tag_context)
        tag_file.close()


if __name__ == "__main__":
    src_dir = "."
    tag_type = "utf-8"
    type_filter = [".cpp", ".h", ".hpp", ".cxx"]

    for dir_path, dirs, files in os.walk(src_dir):
        for name in files:
            if os.path.splitext(name)[1] in type_filter:
                file_code_conversion(os.path.join(dir_path, name), tag_type)

