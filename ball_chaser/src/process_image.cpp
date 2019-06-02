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


image_process::image_process()
{
        image_sub_ = nh_->subscribe("/front_camera/rgb/image_raw",10, &image_process::image_process_callback,this);

        drive_client = nh_->serviceClient<ball_chaser::DriveToTarget>("/command_robot");

}
void image_process::move_robot()
{
	
	ball_chaser::DriveToTarget srv;

	switch(pos)
	{
		case 'L':
			srv.request.linear_x = 0.3;
			srv.request.angular_z = 0.3;
			ROS_WARN("Moving Left");
			break;

		case 'R':
			srv.request.linear_x = 0.3;
			srv.request.angular_z = -0.3;
			ROS_WARN("Moving Right");
			break;

		case 'S':
			srv.request.linear_x = 1.0;
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


int main (int argc, char** argv)
{
	ros::init (argc,argv,"process_image");


	ros::spin();

	return 0;

}

