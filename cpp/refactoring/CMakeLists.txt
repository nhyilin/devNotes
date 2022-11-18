cmake_minimum_required(VERSION 3.22)
project(refactoring)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


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

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    add_executable(${PROJECT_NAME}
            src/main.cpp
            src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui
            src/seven/DataManager.cpp src/seven/DataManager.h
            src/seven/Student.h
            src/Thread/MyThread.cpp src/Thread/MyThread.h
            src/Thread/Worker.h
            src/Thread/Controller.cpp src/Thread/Controller.h)
    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Qml Qt5::Quick
            ${Boost_LIBRARIES})
    target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE ./StdAfx.h)
endif ()
