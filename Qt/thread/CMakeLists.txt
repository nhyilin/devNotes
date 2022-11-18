cmake_minimum_required(VERSION 3.23)
project(thread)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(thread main.cpp widget.cpp widget.h widget.ui Work.cpp Work.h)
target_link_libraries(thread
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

