cmake_minimum_required(VERSION 3.22)
project(refactoring)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(MAIN_PATH ${CMAKE_CURRENT_LIST_DIR})
configure_file(CMakeConfig.h.in ${CMAKE_CURRENT_LIST_DIR}/src/param_deliver.h)
# 子文件夹
include(src/seven/CMakeLists.txt)
include(src/Thread/CMakeLists.txt)
include(src/BoostLog/CMakeLists.txt)

set(BOOST_ROOT /Users/peiyilin/env/boost_1_80_0)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost COMPONENTS log thread date_time filesystem REQUIRED)

find_package(Qt5 COMPONENTS
        Core
        Widgets
        Gui
        Qml
        Quick
        REQUIRED)

# main函数相关的文件
aux_source_directory(src MAIN_SRCS)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    add_executable(${PROJECT_NAME}
            ${MAIN_SRCS} ${SEVEN_SRCS} ${THREAD_SRCS} ${BOOST_SRCS} ${MAIN_SRCS})
    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Qml Qt5::Quick
            ${Boost_LIBRARIES})
    target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE src/StdAfx.h)
endif ()
