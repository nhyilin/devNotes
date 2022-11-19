# refactoring

1. 如果需要在vs中开发，则在cmd中执行如下指令，按自己对应路径进行修改
   cmake.exe -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/Qt5.12.5/5.12.5/msvc2017_64/lib/cmake -S C:/devWin/refactoring -B C:/devWin/refactoring/
2. CMake中配置获取当前路径，并生成头文件在编译过程中直接包含，内含一个宏，在本项目中设置为CMakeLists.txt中所在路径




欢迎各位提出issue
