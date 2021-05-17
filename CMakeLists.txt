cmake_minimum_required(VERSION 3.19)
project(WASTE-APP)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")
add_executable(WASTE-APP ${SRC})
