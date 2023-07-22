cmake_minimum_required(VERSION 3.0.2)
project(dinogen)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  message_runtime
  roscpp
  std_msgs
)

add_service_files(
  FILES
  Dinogen.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dinogen
  CATKIN_DEPENDS message_generation message_runtime roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ../../devel/include
)

add_executable(dinogen_server src/dinogen_server.cpp)
target_link_libraries(dinogen_server ${catkin_LIBRARIES})
add_dependencies(dinogen_server dinogen_gencpp)