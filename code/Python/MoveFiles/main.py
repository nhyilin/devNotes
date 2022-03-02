import os
import shutil
import os.path


# 本脚本开发为了方便C++项目中开发完成后，代码服务器维护不够完善时，下载到本地后，第三方库或license文件的替换脚本
# 分为三个函数，第一个是移动src文件夹内所有文件至dest文件夹
# 第二个为移动单个文件,输出时没有再加文件是否替换的判断,因为必要不大
# 第三个函数做删除指定后缀名文件


def copy_files_all_folder(src, dest):
    # src为源文件夹，dest为目标文件夹
    src_files = os.listdir(src)
    for file_name in src_files:
        full_file_name = os.path.join(src, file_name)
        dest_file_name = os.path.join(dest, file_name)
        if os.path.isfile(full_file_name):
            if (os.path.exists(dest_file_name)):
                print(full_file_name + "  --  was moved with implacement into " + (dest))
            else:
                print(full_file_name + "  --  just move into " + (dest))
            shutil.copy(full_file_name, dest)


def copy_single_file(file_name, dest_path):
    if os.path.isfile(file_name):
        shutil.copy(file_name, dest_path)
        print(file_name + "  --  was moved into  --  " + (dest_path))


def deleteFile(targetDir, type_filter):
    for x in type_filter:
        for file in os.listdir(targetDir):
            targetFile = os.path.join(targetDir, file)
            array = map(file.endswith, x)
            if True in array:
                os.remove(targetFile)


# demo of using

copy_files_all_folder('D:/myDevlop/CSTK/cstkKernel/x64/Release', 'D:/myDevlop/CSTK/TZSatelliteSimTool/release')
copy_single_file('D:/myDevlop/CSTK/related/VVP_LicenseV60.lic', 'D:/myDevlop/CSTK/TZSatelliteSimTool/release')
# deleteFile("D:/杂/1",[".txt", ".h", ".hpp", ".cxx"])
