# Generated from chartthemes.pro.

cmake_minimum_required(VERSION 3.16)
project(Elevator VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(MAIN_PATH ${PROJECT_SOURCE_DIR})
configure_file(src/param_deliver.h.in ../../param_deliver.h)

if (NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif ()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/chartthemes")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts Gui)

add_executable(chartthemes WIN32 MACOSX_BUNDLE
        src/main.cpp
        src/themewidget.cpp src/themewidget.h src/themewidget.ui
        src/DataManager.cpp src/DataManager.h src/Utils.cpp src/Utils.h src/Net.cpp src/Net.h src/Config.h)
target_link_libraries(chartthemes PUBLIC
        Qt::Charts
        Qt::Core
        Qt::Gui
        )

install(TARGETS chartthemes
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
        )
