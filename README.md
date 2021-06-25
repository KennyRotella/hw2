SECOND ROBOTICS PROJECT

1.  10634706 Massimo Del Tufo
2.  10704486 Priyanka Rajendran  
  
-small description of the files inside the archive
Launch files:
  gmapping_launch.launch: to create the map using gmapping
  gmapping_launch.xml: gmapping configuration file
  robot_localization: to localize the robot using imutools,amcl and ekf
  amcl.xml: amcl configuration file
maps:
  contains the map generated using different bags.
params:
  configuration file that contains the parameters for localization.
rviz:
  rviz configuration file for gmapping and localization.
src:
  publishes sensor messages.

-structure of the tf tree
  frames.dot

-name of the bag used to create the map and bags to test
  used tf_remapped bags, 2.bag to create the map and 1.bag 3.bag to test it

-description of how to start/use the nodes
  to create the map:
	  roslaunch hw2 gmapping_launch.launch
	  rosbag play --clock 2.bag

  to do localization:
    roslaunch hw2 robot_localization.launch
    rosbag play --clock 1.bag [or 3.bag]

-small report to explain the sensors choice (why you used a specific sensor in
robot localization, and how you setup the config matrix, why some true and
some false)
  we used imu from the Pixhawk, the first row is false since it is a accel/gyro, we set the yaw angular velocity and since it is a skid steering robot we set only the x acceleration (not y accel) to true (in this scenario the robot does not drift too much). We used also the scout odom, we initially set the x and yaw velocities and got a good result, we then used directly the x,y positions and yaw orientation from scout/odom and the covariance got better.

-info you think are important/interesting
  we tried to use also the imu from the camera, in the src there is a node for republish it, we did not notice any improvement.
