//standard includes
#include "ros/ros.h"
#include <sensor_msgs/Imu.h>

//message_filters includes
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

//typedef for the message filters Time policy
typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::Imu> MySyncPolicy;

void callback(const sensor_msgs::Imu::ConstPtr& msg_gyro, const sensor_msgs::Imu::ConstPtr& msg_accel, ros::Publisher imu_pub){

	sensor_msgs::Imu new_sensor_msg;

	new_sensor_msg.header.stamp = msg_gyro->header.stamp;
	new_sensor_msg.header.frame_id =  msg_gyro->header.frame_id;

	new_sensor_msg.angular_velocity.x = msg_gyro->angular_velocity.x;
	new_sensor_msg.angular_velocity.y = msg_gyro->angular_velocity.y;
	new_sensor_msg.angular_velocity.z = msg_gyro->angular_velocity.z;

	new_sensor_msg.angular_velocity_covariance = msg_gyro->angular_velocity_covariance;

	new_sensor_msg.linear_acceleration.x = msg_accel->linear_acceleration.x;
	new_sensor_msg.linear_acceleration.y = msg_accel->linear_acceleration.y;
	new_sensor_msg.linear_acceleration.z = msg_accel->linear_acceleration.z;

	new_sensor_msg.linear_acceleration_covariance = msg_accel->linear_acceleration_covariance;

	imu_pub.publish(new_sensor_msg);

}


int main(int argc, char**argv){
	ros::init(argc, argv, "imu_camera_republisher");
	ros::NodeHandle nh;

	ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("/camera_imu_raw", 1);
	message_filters::Subscriber<sensor_msgs::Imu> sub_gyro(nh, "camera/gyro/sample", 1);
	message_filters::Subscriber<sensor_msgs::Imu> sub_accel(nh, "camera/accel/sample", 1);

	message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(5), sub_gyro, sub_accel);
	sync.registerCallback(boost::bind(&callback, _1, _2, imu_pub));

	ros::spin();

	return 0;


}