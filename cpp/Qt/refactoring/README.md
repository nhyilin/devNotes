# refactoring

1. 生成Xcode项目：`cmake -G "Xcode" .`，`.`代表当前目录，即CMakeLists.txt所在的目录，建议最好新建Xcode文件夹，并在Xcode文件夹内执行`cmake -G "Xcode" ../`。如果报错找不到编译器，可以使用：`.sudo xcode-select --switch /Applications/Xcode.app/`
2. 如果需要在vs中开发，则在cmd中执行如下指令，按自己对应路径进行修改
   cmake.exe -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/Qt5.12.5/5.12.5/msvc2017_64/lib/cmake -S C:/devWin/refactoring -B C:/devWin/refactoring/
3. CMake中配置获取当前路径，并生成头文件在编译过程中直接包含，内含一个宏，在本项目中设置为CMakeLists.txt中所在路径

欢迎各位提出issue
