# Udacity Robotics Nanodegree
# Project #2: Go Chase It

## Introduction
This is a project for Udacity's Robotics NanoDegree. It's a robot that is capable of finding a white ball in a forward-facing camera, and driving toward it.

## Concepts and Classes
Concepts explored in this project:

  - Gazebo model and world-building
  - Gazebo plugins
  - URDF
  - ROS publishers, subscribers, and services
  - C++

## Getting Started
To view this project, you must have Gazebo and ROS installed on Linux. [Click here for Gazebo download and installation instructions](http://gazebosim.org). [Click here for ROS installation instructions](http://wiki.ros.org/ROS/Installation).

With Gazebo and ROS installed, you first need to create a catkin workspace. Navigate to your home directory and execute:
```
$ mkdir -p catkin_ws/src
$ cd catkin_ws/src
$ catkin_init_workspace
```

Then download/clone the repository to a folder outside the catkin workspace, and then copy the ```my_robot``` and  ```ball_chaser``` folders, and the ```CMakeLists.txt``` file into the ```src``` folder of the catkin workspace. Once you've done that, navigate to the top level of the catkin workspace and execute the following to build the executables:

```
$ catkin_make
```

Next, execute the following to open Gazebo with the robot in it:
```
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

Open another terminal, navigate to the top level catkin workspace, and execute:
```
$ source devel/setup.bash
$ rosrun ball_chaser drive_bot
```

And finally, open a third terminal and execute:
```
$ source devel/setup.bash
$ rosrun ball_chaser/process_image
```

This will start the node that processes an image from the forward-facing camera and commands the robot to chase the white ball in its field of view.
