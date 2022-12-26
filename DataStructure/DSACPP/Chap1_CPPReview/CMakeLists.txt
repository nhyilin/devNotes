cmake_minimum_required(VERSION 3.23)
project(Chap1_CPPReview)

set(CMAKE_CXX_STANDARD 23)

#AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_executable(Chap1_CPPReview  test_first.cpp first.h)
target_precompile_headers(Chap1_CPPReview PRIVATE ../../StdAfx.h)
