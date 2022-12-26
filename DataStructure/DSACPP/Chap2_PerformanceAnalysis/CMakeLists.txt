cmake_minimum_required(VERSION 3.23)
project(Chap2_PerformanceAnalysis)

set(CMAKE_CXX_STANDARD 23)

#AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_executable(Chap2_PerformanceAnalysis main.cpp)
target_precompile_headers(Chap2_PerformanceAnalysis PRIVATE ../../StdAfx.h)
