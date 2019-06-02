#include "ball_chaser/ball_chaser_base.h"


drive_bot::drive_bot()
{
   nh_ = new ros::NodeHandle("~");
   motor_command_publisher = nh_->advertise<geometry_msgs::Twist>("/cmd_vel",1);
   command_robot = nh_->advertiseService("/command_robot",&drive_bot::handle_drive_request,this);

}


bool drive_bot::handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
   
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
   drive_bot drive;
   ros::Rate r(20);

   while(ros::ok())
   {
     ros::spinOnce();
     r.sleep();
   }  
   return 0;
}
