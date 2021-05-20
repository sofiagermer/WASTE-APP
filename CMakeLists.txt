cmake_minimum_required(VERSION 3.19)
project(WASTE-APP)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build GraphViewerCpp
#set(GRAPHVIEWER_PATH lib/GraphViewerCpp)
#add_subdirectory(${GRAPHVIEWER_PATH})
#include_directories(${GRAPHVIEWER_PATH}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")
add_executable(WASTE-APP ${SRC})

#target_link_libraries(WASTE-APP graphviewer)


#cmake_minimum_required(VERSION 3.17)

