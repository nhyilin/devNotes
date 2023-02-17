# Generated from chartthemes.pro.

cmake_minimum_required(VERSION 3.16)
project(chartthemes VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if (NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif ()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/chartthemes")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts Gui)

add_executable(chartthemes WIN32 MACOSX_BUNDLE
        main.cpp
        themewidget.cpp themewidget.h themewidget.ui
        DataManager.cpp DataManager.h)
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
