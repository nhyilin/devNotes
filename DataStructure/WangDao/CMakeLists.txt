cmake_minimum_required(VERSION 3.23)
project(WangDao)

set(CMAKE_CXX_STANDARD 23)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_executable(WangDao ${SRC_LIST})
target_precompile_headers(WangDao PRIVATE ../StdAfx.h)
