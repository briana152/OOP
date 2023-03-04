cmake_minimum_required(VERSION 3.21)
project(colocviu_santa)

set(CMAKE_CXX_STANDARD 14)
set(UTIL_SOURCE_FILES util/IoBase.h util/IoBase.cpp util/functions.h util/functions.cpp)

add_executable(colocviu_santa main.cpp ${UTIL_SOURCE_FILES})
