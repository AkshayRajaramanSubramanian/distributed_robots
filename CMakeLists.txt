cmake_minimum_required(VERSION 2.8.3)
project(distributed_robots)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(FILES RobotPose.msg)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(publish_positions src/publisher.cpp)
target_link_libraries(publish_positions ${catkin_LIBRARIES})

add_executable(subscribe_positions src/subscriber.cpp)
target_link_libraries(subscribe_positions ${catkin_LIBRARIES})
