cmake_minimum_required(VERSION 3.24)
project(CppUsingPythonLib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CppUsingPythonLib main.cpp)
target_link_libraries(CppUsingPythonLib
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

