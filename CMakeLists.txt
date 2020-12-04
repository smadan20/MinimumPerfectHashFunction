cmake_minimum_required(VERSION 3.17)
project(BBHash_Implementation)

find_package(xxHash CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(BBHash_Implementation main.cpp MPHF.cpp MPHF.h)
target_link_libraries(BBHash_Implementation PRIVATE xxHash::xxhash)