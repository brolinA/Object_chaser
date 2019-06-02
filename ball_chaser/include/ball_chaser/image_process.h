#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#include "ball_chaser/DriveToTarget.h"
#include <string>

class image_process
{
 public:
  ros::NodeHandle* nh_;
  ros::Subscriber image_sub_;
  ros::ServiceClient drive_client;
  char pos;

  image_process();
  void move_robot();
  void image_process_callback(const sensor_msgs::Image img);

};
