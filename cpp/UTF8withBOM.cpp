#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

// 写入文件的内容为 UTF-8 编码，支持 BOM
bool convertFileToUtf8(const std::string& filePath, bool withBom) {
    // 打开文件，读取内容
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading: " << filePath << std::endl;
        return false;
    }

    // 读取文件内容
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // 打开文件，重新写入为 UTF-8
    std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return false;
    }

    // 如果需要写入 BOM，则在文件开头写入 BOM
    if (withBom) {
        const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
        outFile.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    }

    // 写入文件内容
    outFile.write(content.c_str(), content.size());
    outFile.close();

    std::cout << "Converted file: " << filePath << " to UTF-8 " << (withBom ? "with BOM" : "without BOM") << std::endl;
    return true;
}

// 递归处理目录，查找指定扩展名的文件
void processDirectory(const std::string& directoryPath, bool withBom) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                // 获取文件扩展名
                std::string extension = entry.path().extension().string();
                if (extension == ".cpp" || extension == ".c" || extension == ".h" || extension == ".hpp") {
                    convertFileToUtf8(entry.path().string(), withBom);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing directory: " << e.what() << std::endl;
    }
}

int main() {
    // 设置目标目录路径
    std::string targetDirectory = "D:/demo/cppSocket"; // 替换为你的目标目录
    bool withBom = true; // 设置为 true 表示使用 UTF-8 with BOM，false 表示不使用 BOM

    std::cout << "Starting conversion in directory: " << targetDirectory << std::endl;
    processDirectory(targetDirectory, withBom);
    std::cout << "Conversion completed." << std::endl;

    return 0;
}
