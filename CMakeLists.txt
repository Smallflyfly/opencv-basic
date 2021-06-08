cmake_minimum_required(VERSION 3.17)
project(opencv_basic)

set(CMAKE_CXX_STANDARD 14)

#find_package(OpenCV)
set(OpenCV_DIR D:\\opencv\\build)
find_package(OpenCV 3.4 REQUIRED)
set(OpenCV_FOUND 1)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencv_basic
        camera.cpp)

target_link_libraries(opencv_basic ${OpenCV_LIBS})

