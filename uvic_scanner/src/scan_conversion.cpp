#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>
#include <uvic_msgs/LSToPC.h>

laser_geometry::LaserProjection projector;

bool conversion(uvic_msgs::LSToPC::Request &req, uvic_msgs::LSToPC::Response &res) {
  projector.projectLaser(req.scan, res.pointcloud);
  res.empty = ( res.pointcloud.data.size() == 0 ) ? true : false;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "scan_conversion");
  ros::NodeHandle n;
 
  ros::ServiceServer conversion_service = n.advertiseService("scan_to_pointcloud", conversion);
  ROS_INFO("[scan_conversion] Ready to convert sensor_msgs::LaserScan to sensor_msgs::PointCloud2");
  
  ros::spin();
  return 0;
}
