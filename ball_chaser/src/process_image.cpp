#include "ball_chaser/image_process.h"

/*

Short hands used in this code
-----------------------------

L - Turn Left.
R - Turn Right.
S - Move Straight.
N - No action/stop.

The image from the /front_camera/rgb/image_raw used here is 1200x1200 in size.

The image is split into three sections along the width. 

Pixel 0 to 650    - Left
Pixel 651 to 750  - Center
Pixel 751 to 1200 - Right

Depending on where the first white pixle lies, the robot moves either left, right or straight.

*/

double st_lin,left_lin,left_ang,right_lin,right_ang;


image_process::image_process()
{
	nh_ = new ros::NodeHandle("~");
        image_sub_ = nh_->subscribe("/front_camera/rgb/image_raw",10, &image_process::image_process_callback,this);
        drive_client = nh_->serviceClient<ball_chaser::DriveToTarget>("/command_robot");

}
void image_process::move_robot()
{
	
	ball_chaser::DriveToTarget srv;

	switch(pos)
	{
		case 'L':
			srv.request.linear_x = left_lin;
			srv.request.angular_z = left_ang;
			ROS_WARN("Moving Left");
			break;

		case 'R':
			srv.request.linear_x = right_lin;
			srv.request.angular_z = right_ang;
			ROS_WARN("Moving Right");
			break;

		case 'S':
			srv.request.linear_x = st_lin;
			srv.request.angular_z = 0.0;
			ROS_WARN("Moving Straight");
			break;

		case 'N':
			srv.request.linear_x = 0.0;
			srv.request.angular_z = 0.0;
			ROS_WARN("Ball Not in View");
			break;

	}

	drive_client.call(srv);


}

void image_process::image_process_callback(const sensor_msgs::Image img)
{

	int column;
	int white_pixel = 255;
        ROS_INFO("Processing Image");

	pos = 'N';

	for (int i = 0; i < img.height*img.step; i=i+3)
	{
		if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel)
		{
			column = i%img.width;

			if (column <= 650)
				pos = 'L';

			else if (column <= 750)
				pos = 'S' ;

			else
				pos = 'R';

			break;
		}

	}

	image_process::move_robot();
}

bool load_params(ros::NodeHandle *nh)
{
  bool param_loaded = nh->getParam("/straight_velocity/linear", st_lin);
  param_loaded = param_loaded && nh->getParam("/left_turn_velocity/linear", left_lin);
  param_loaded = param_loaded && nh->getParam("/left_turn_velocity/angular", left_ang);
  param_loaded = param_loaded && nh->getParam("/right_turn_velocity/linear", right_lin);
  param_loaded = param_loaded && nh->getParam("/right_turn_velocity/angular", right_ang);
  
  return param_loaded;
}


int main (int argc, char** argv)
{
	ros::init (argc,argv,"process_image");
	ros::NodeHandle nh("~");
	image_process image_processor;	
	ros::Rate r(20);

	bool params_loaded = load_params(&nh);
	if (!params_loaded)
	{
	    // shutdowns the code if params not loaded properly
	    ROS_ERROR("Check Velocity Params!!!");
	    ros::shutdown();
	}

   	while(ros::ok())
   	{
     	ros::spinOnce();
     	r.sleep();
   	}

	return 0;

}

