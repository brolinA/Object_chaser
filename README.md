# Object_chaser Package

The package contains a Mobile robot model created using **solid works** and housed in a custom made simulation environment. The robot model also contain a **RBG camera** and a **Laser Range Finder** to perceive its environment

## Requirement

- Gaezebo (Version 7 preferable). You can find help for installing gazebo and other related packages [here](http://gazebosim.org/tutorials?tut=ros_installing)
- ROS Kinetic Kame or higher

## Working with this package

You can download the package by typing the following command in your terminal

```
$ mkdir object_chaser
$ cd custom_enviroment
$ git init
$ git clone https://github.com/brolinA/Object_chaser.git
```

You can download only the custom simulation environment from [here](https://github.com/brolinA/build_my_world.git)

### robot_model directory

This package contains the robot model and the simulation environment along with the required gazebo plug-in so that you can use this environment for you own projects.

Launch the world using 

	`roslaunch robot_model world.launch`

**Some useful links**
 - [Differential drive plug-in](https://bitbucket.org/osrf/gazebo/src/afe08834571835008fa7419f1feba5b7f89b9d62/plugins/DiffDrivePlugin.cc?at=gazebo7&fileviewer=file-view-default)
 - [Camera plug-in](https://bitbucket.org/osrf/gazebo/src/afe08834571835008fa7419f1feba5b7f89b9d62/plugins/CameraPlugin.cc?at=gazebo7)

### ball_chaser directory

This package is used to drive the mobile robot using the **Request-Response** architecture rather than the usual **Pub-Sub** architecture.

Whenever a new message arrive at the `camera` topic the callback `image_process_callback` is invoked. This callback process the image to look for white pixles. Depending on where the pixel lies in the image i.e, left,right or in the center, a service call is made to the service named `/command_robot`. This service drives the robot with the desired velocities requested by the service call.

