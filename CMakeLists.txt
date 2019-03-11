cmake_minimum_required(VERSION 2.8.3)
project(rosparam_handler_tests)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

set(CMAKE_CXX_FLAGS "-std=c++1y $ENV{CMAKE_CXX_FLAGS}")


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosparam_handler
  rospy
  dynamic_reconfigure
)

generate_ros_parameter_files(
  config/rosparam.params
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rosparam_handler_tests
#  CATKIN_DEPENDS roscpp rosparam_handler rospy
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(example_node src/example_node.cpp)


target_link_libraries(example_node ${catkin_LIBRARIES})

add_dependencies(example_node ${PROJECT_NAME}_gencfg) # For dynamic_reconfigure
add_dependencies(example_node ${PROJECT_NAME}_genparam) # For rosparam_handler




