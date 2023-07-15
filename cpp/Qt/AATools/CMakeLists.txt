cmake_minimum_required(VERSION 3.25)
project(AATools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(MAIN_PATH ${PROJECT_SOURCE_DIR})
configure_file(${CMAKE_CURRENT_LIST_DIR}/param_deliver.h.in ${CMAKE_CURRENT_LIST_DIR}/param_deliver.h)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(AATools main.cpp src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui src/oe2tle/oe2tle.cpp src/oe2tle/oe2tle.h src/info.h pch.h)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/pch.h)
target_link_libraries(AATools
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

