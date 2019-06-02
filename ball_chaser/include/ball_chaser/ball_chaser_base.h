#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

#ifndef BALL_CHASER_BASE_H
#define BALL_CHASER_BASE_H


class drive_bot
{
  
 public:
  drive_bot();
  bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res);

  private:
  ros::Publisher motor_command_publisher;
  ros::ServiceServer command_robot;

  geometry_msgs::Twist motor_command;

  ros::NodeHandle* nh_;



};
#endif
