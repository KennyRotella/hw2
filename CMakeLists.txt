cmake_minimum_required(VERSION 3.0.2)
project(robotics_project)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
  roscpp 
  std_msgs
  sensor_msgs
  message_filters
  rospy
  )



## Declare a catkin package
catkin_package( 
  CATKIN_DEPENDS
  std_msgs
  sensor_msgs
  message_filters
)




## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(imu_camera_republisher_exec src/imu_camera_republisher.cpp)
target_link_libraries(imu_camera_republisher_exec ${catkin_LIBRARIES})
