export ROS_MASTER_URI=http://192.168.106.1:11311
export ROS_HOSTNAME=$(hostname -I)
roslaunch turtlebot_teleop keyboard_teleop.launch
