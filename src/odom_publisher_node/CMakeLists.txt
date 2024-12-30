cmake_minimum_required(VERSION 3.0.2)
project(odom_publisher_node)

## 找到依赖
find_package(catkin REQUIRED COMPONENTS
  roscpp
  nav_msgs
  geometry_msgs
)

## 声明 catkin 包
catkin_package()

## 指定编译的目标
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## 添加可执行文件
add_executable(odom_publisher_node src/odom_publisher.cpp)

## 链接依赖
target_link_libraries(odom_publisher_node
  ${catkin_LIBRARIES}
)

