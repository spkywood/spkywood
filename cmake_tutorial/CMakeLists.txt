cmake_minimum_required(VERSION 3.22)

project(cmake_tutorial)

add_definitions(-std=c++11)
# set( CMAKE_CXX_FLAGS "-std=c++11" )   # 同上，指定 c++11 标准
# set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

# OpenCV
# set(OpenCV_DIR /home/ubuntu/opencv-4.4.0/build)
find_package( OpenCV 4 REQUIRED )

# print message
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories( "/usr/local/Cellar/eigen/3.4.0_1/include/eigen3" )

include_directories( ${OpenCV_INCLUDE_DIRS} )   # 添加头文件

add_executable( test main.cpp )
target_link_libraries( test ${OpenCV_LIBS} )    # 链接OpenCV库