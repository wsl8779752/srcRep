CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
#MARK_AS_ADVANCED( FORCE CMAKE_BACKWARDS_COMPATIBILITY )


###################################################
#                                                 #
#       Start project customization section       #
#                                                 #
###################################################

PROJECT(explosion)
include_directories(/usr/include/eigen3)
include_directories(PROJECT_SOURCE_DIR)
add_executable(kk main.cpp explosionChain.cpp)
target_link_libraries(kk orocos-kdl)
