#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the comman_robot service to drive the robot in the
// specified direction
void drive_robot(float lin_x, float ang_z)
{
  // TODO: Request a service and pass the velocities to it to drive the robot
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;
  client.call(srv);
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
  // TODO: Loop through each pixel in the image and check if there's a bright white one
  // Then, identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  // Request a stop when there's no white ball seen by the camera

  // Since the ball is level with the camera, only have to scan the middle third of the image
  int scan_start = img.data.size() / 3;
  int scan_end = img.data.size() * 2 / 3;

  bool ball_found = false;

  // Scan each pixel looking for a white one
  for (int i=scan_start; i+2<scan_end; i+=3) {

    int red_channel = img.data[i];
    int green_channel = img.data[i+1];
    int blue_channel = img.data[i+2];

    if (red_channel == 255 && green_channel == 255 && blue_channel == 255)
    {
      ball_found = true;
      int x_position = (i % (img.width * 3)) / 3;

      if (x_position < img.width / 3)
      {
        drive_robot(0.5, 0.5);
      }
      else if (x_position > img.width * 2 / 3)
      {
        drive_robot(0.5, -0.5);
      }
      else
      {
        drive_robot(0.5, 0.0);
      }
    } 
  }

  if (!ball_found)
  {
    drive_robot(0.0, 0.0);
  }
}

int main(int argc, char** argv)
{
  // Initialize the process_image node and create a handle to it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  // Subscribe to /camera/rgb/image_raw topic to read the image data inside the
  // process_image_callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  // Handle ROS communication events
  ros::spin();

  return 0;
}
