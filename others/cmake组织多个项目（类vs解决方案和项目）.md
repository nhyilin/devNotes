如果你子项目和主项目都是独立的可执行文件，那么可以使用以下方法来用CMake组织起来：

- 在顶层目录下创建一个CMakeLists.txt文件，使用`project`指令为整个项目设置一个名称，使用`add_subdirectory`指令为每个子项目添加一个子目录¹²。
- 在每个子目录下创建一个CMakeLists.txt文件，使用`project`指令为每个子项目设置一个名称，使用`add_executable`指令为每个子项目创建一个可执行目标²。
- 如果你的子项目之间有依赖关系，你可以使用`target_link_libraries`指令来链接其他子项目的可执行目标，或者使用别名来简化引用²。
- 如果你的子项目需要包含其他头文件或库，你可以使用`target_include_directories`或者`target_link_libraries`指令来设置相应的路径²。

下面是一个简单的示例，假设有三个子项目：app1, app2, app3，其中app1依赖于app2和app3，而app2和app3没有依赖关系。

- 顶层CMakeLists.txt文件：

```cmake
# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(my_project)

# Add sub directories
add_subdirectory(app1)
add_subdirectory(app2)
add_subdirectory(app3)
```

- app1/CMakeLists.txt文件：

```cmake
# Set the project name
project(app1)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the executable targets from app2 and app3 using their aliases app::app2 and app::app3
target_link_libraries(${PROJECT_NAME} app::app2 app::app3)
```

- app2/CMakeLists.txt文件：

```cmake
# Set the project name
project(app2)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Create an alias for the executable target
add_executable(app::app2 ALIAS ${PROJECT_NAME})
```

- app3/CMakeLists.txt文件：

```cmake
# Set the project name
project(app3)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Create an alias for the executable target
add_executable(app::app3 ALIAS ${PROJECT_NAME})
```


(1) CMake基础 第13节 构建子项目 - 橘崽崽啊 - 博客园. https://www.cnblogs.com/juzaizai/p/15069693.html.
(2) 模块化项目管理：CMake中的子目录和模块化构建 - 知乎. https://zhuanlan.zhihu.com/p/648590757.
(3) Visual Studio 中的 CMake 项目 | Microsoft Learn. https://learn.microsoft.com/zh-cn/cpp/build/cmake-projects-in-visual-studio?view=msvc-170.