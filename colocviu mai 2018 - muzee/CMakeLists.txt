cmake_minimum_required(VERSION 3.21)
project(colocviu_mai2018_muzee)

set(CMAKE_CXX_STANDARD 17)

set(UTIL_SOURCE_FILES util/IoBase.h util/IoBase.cpp util/functions.h util/functions.cpp)

add_executable(colocviu_mai2018_muzee main.cpp ${UTIL_SOURCE_FILES})
