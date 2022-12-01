CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(cppMath)
set(CMAKE_CXX_STANDARD 23)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
INCLUDE_DIRECTORIES("./thirdpart/eigen/include/eigen3" ${Python3_INCLUDE_DIRS}) #("${EIGEN3_INCLUDE_DIR}")
SET(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
#IF(NOT EIGEN3_INCLUDE_DIR)
#    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
#ENDIF()

# 找到src目录及其子目录下的所有c文件和h文件
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp" "src/*.c" "src/*.cc")
set(sources src/EigenPolyfit/eigen_polyfit.cpp)

#add_executable(polyfit ${sources})
file(GLOB_RECURSE PROJECT_HEADERS "src/*.hpp" "src/*.h" "src/*.hh")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}  ${PROJECT_HEADERS})

target_link_libraries(${PROJECT_NAME}  ${Python3_LIBRARIES})
