cmake_minimum_required(VERSION 3.25)
project(thread_msg_server)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT /Path/To/boost_1_82_0)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost COMPONENTS log thread date_time filesystem REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(${PROJECT_NAME} thread_msg_server.cpp xmsg_server.cpp xthread.cpp xmsg_server.h xthread.h)

    target_link_libraries(${PROJECT_NAME}
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
    )
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif ()
