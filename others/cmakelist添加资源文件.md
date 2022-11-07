cmakelist添加资源文件，一般将qrc添加即可将所有图片等资源完成索引。

```cmake
cmake_minimum_required(VERSION 3.16)
project(TZSatelliteSimTool VERSION 1.0 LANGUAGES CXX)

//这里
FILE(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.qrc)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)//非必要

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Sql WebChannel WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS PrintSupport Widgets)
//这里
set(QRC_SOURCE_FILES ./Sources/controlimage.qrc ./Sources/EchartsConfig.qrc ./Sources/imagesource.qrc)
//这里
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
//这里
source_group("Resource Files" FILES ${QRC_SOURCE_FILES})
add_executable(TZSatelliteSimTool
    //这里
    ${QRC_FILES}
    main.cpp
    mainmenu.cpp mainmenu.h mainmenu.ui
    mainwindow.cpp mainwindow.h mainwindow.ui
    ...
)
target_precompile_headers(TZSatelliteSimTool PUBLIC stable.h)//预编译头文件
target_compile_definitions(TZSatelliteSimTool PUBLIC
    QT_DEPRECATED_WARNINGS
)
target_link_libraries(TZSatelliteSimTool PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Qt5::Sql
    Qt5::WebChannel
    Qt5::WebEngineWidgets
)


#install(TARGETS TZSatelliteSimTool
#    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
#    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
#    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
#)
```
