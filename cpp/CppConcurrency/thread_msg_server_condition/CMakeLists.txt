cmake_minimum_required(VERSION 3.25)
project(thread_msg_server)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_HOST_APPLE)
    message ("set Macos environment path")
    set(BOOST_ROOT /Users/peiyilin/env/boost_1_82_0)
elseif (CMAKE_HOST_WIN32)
    message ("set Windows environment path")
elseif (UNIX AND NOT APPLE)
    message ("set Linux environment path")
endif ()

set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost COMPONENTS log thread date_time filesystem REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(${PROJECT_NAME} thread_msg_server.cpp xmsg_server.cpp xthread.cpp xmsg_server.h xthread.h)

    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif ()
