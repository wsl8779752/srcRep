CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
#MARK_AS_ADVANCED( FORCE CMAKE_BACKWARDS_COMPATIBILITY )


###################################################
#                                                 #
#       Start project customization section       #
#                                                 #
###################################################

PROJECT(explosion)
FILE(GLOB EXP_SRC [^.]*.cpp)
include_directories(/usr/include/eigen3)
include_directories(/usr/local/include/kdl)
MESSAGE(STATUS "project source dir is: ${PROJECT_SOURCE_DIR}")
add_executable(main ${EXP_SRC})
MESSAGE(STATUS "project source dir is: ${EXP_SRC}")
target_link_libraries(main orocos-kdl)
