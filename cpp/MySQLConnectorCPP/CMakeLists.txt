cmake_minimum_required(VERSION 3.24)
project(MySQLConnectorCPP)

set(CMAKE_CXX_STANDARD 23)
include_directories(/usr/local/mysql/include /usr/local/mysql-connector-c++/include)
link_directories(/usr/local/mysql/lib /usr/local/mysql-connector-c++/lib64/)

aux_source_directory(. DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})


target_link_libraries(${PROJECT_NAME} libmysqlcppconn.dylib -lssl -lcrypto)
