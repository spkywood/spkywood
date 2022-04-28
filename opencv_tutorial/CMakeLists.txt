cmake_minimum_required(VERSION 3.22)

project(cmake_tutorial)

add_definitions(-std=c++11)
# set( CMAKE_CXX_FLAGS "-std=c++11" )   # 同上，指定 c++11 标准
# set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

find_package( OpenCV 4 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )   # 添加头文件

add_executable( fld_lines src/fld_lines.cpp )
add_executable( shape_example src/shape_example.cpp )

target_link_libraries( fld_lines ${OpenCV_LIBS} )    # 链接OpenCV库
target_link_libraries( shape_example ${OpenCV_LIBS} )    # 链接OpenCV库