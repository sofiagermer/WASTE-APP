cmake_minimum_required(VERSION 3.19)
project(WASTE_APP)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")
add_executable(WASTE_APP ${SRC} WASTE_APP src/main.cpp)
