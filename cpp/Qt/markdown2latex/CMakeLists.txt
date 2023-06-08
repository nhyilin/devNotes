cmake_minimum_required(VERSION 3.25)
project(markdown2latex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(MAIN_PATH ${PROJECT_SOURCE_DIR})
configure_file(./src/param_deliver.h.in ../src/param_deliver.h)

set(BOOST_ROOT /Users/peiyilin/env/boost_1_82_0)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost COMPONENTS log thread date_time filesystem REQUIRED)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(${PROJECT_NAME} src/main.cpp src/MdFile.cpp src/MdFile.h src/mainwindow.h src/mainwindow.ui src/mainwindow.cpp src/ParseINI.cpp src/ParseINI.h src/InitLog.cpp src/InitLog.h)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Widgets)

    #预编译头文件
    target_precompile_headers(markdown2latex PRIVATE src/pch.h)

else ()
    message(FATAL_ERROR "Boost not found!")
endif ()











