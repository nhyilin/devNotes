cmake_minimum_required(VERSION 3.23)
project(BOOSTlog)

set(CMAKE_CXX_STANDARD 23)

set(BOOST_ROOT /Users/peiyilin/env/boost_1_80_0)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost COMPONENTS log thread date_time filesystem REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(${PROJECT_NAME} main.cpp InitLog.cpp InitLog.h ParseINI.cpp ParseINI.h)
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
endif()