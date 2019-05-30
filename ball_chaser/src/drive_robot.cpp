#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

ros::Publisher motor_command_publisher;
ros::ServiceServer command_robot;

bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
   geometry_msgs::Twist motor_command;
   
   motor_command.linear.x  = req.linear_x;
   motor_command.angular.z = req.angular_z;
 
   motor_command_publisher.publish(motor_command);

   res.feedback = "Motor command successfully written to joint";
   ROS_INFO_STREAM(res.feedback);
   
   return true;
}

int main(int argc, char** argv)
{
   ros::init(argc,argv,"drive_robot");
   
   ros::NodeHandle nh;
   
   motor_command_publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);

   command_robot = nh.advertiseService("/command_robot",handle_drive_request);

   ros::spin();
   
   return 0;
}
