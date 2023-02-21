cmake_minimum_required(VERSION 3.16)
project(test_pangolin)

find_package(Pangolin 0.5 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(test_pangolin test.cpp)
target_link_libraries(test_pangolin ${Pangolin_LIBRARIES})