cmake_minimum_required(VERSION 3.23)
project(BUAA)

set(CMAKE_CXX_STANDARD 23)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_executable(BUAA ${SRC_LIST})
target_precompile_headers(BUAA PRIVATE ../StdAfx.h)
