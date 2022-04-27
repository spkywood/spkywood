cmake_minimum_required(VERSION 2.6)

project(cmake_tutorial)

add_definitions(-std=c++11)
# set( CMAKE_CXX_FLAGS "-std=c++11" )   # 同上，指定 c++11 标准
# set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

# OpenCV
set(OpenCV_DIR /home/ubuntu/opencv-4.4.0/build)
find_package( OpenCV 4 REQUIRED )


include_directories( ${OpenCV_INCLUDE_DIRS} )   # 添加头文件

add_executable( test main.cpp )
target_link_libraries( test ${OpenCV_LIBS} )    # 链接OpenCV库