cmake_minimum_required(VERSION 3.23)
project(TP_project)

set(CMAKE_CXX_STANDARD 20)

add_library(Field Field.cpp)

add_executable(TP_project main.cpp)

target_link_libraries(TP_project Field)