cmake_minimum_required(VERSION 3.23)
project(DataStructure)

set(CMAKE_CXX_STANDARD 23)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_executable(DataStructure ${SRC_LIST} )
target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE ./StdAfx.h)
