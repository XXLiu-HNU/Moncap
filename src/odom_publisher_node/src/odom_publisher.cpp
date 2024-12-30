#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>

class OdomPublisher {
public:
    OdomPublisher() {
        // 初始化订阅和发布者
        pose_sub_ = nh_.subscribe("/vrpn_client_node/uav1/pose", 10, &OdomPublisher::poseCallback, this);
        twist_sub_ = nh_.subscribe("/vrpn_client_node/uav1/twist", 10, &OdomPublisher::twistCallback, this);
        odom_pub_ = nh_.advertise<nav_msgs::Odometry>("/vision_odom", 10);
    }

private:
    ros::NodeHandle nh_;
    ros::Subscriber pose_sub_;
    ros::Subscriber twist_sub_;
    ros::Publisher odom_pub_;
    geometry_msgs::PoseStamped latest_pose_;
    geometry_msgs::TwistStamped latest_twist_;

    void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& pose_msg) {
        latest_pose_ = *pose_msg;
        publishOdom();
    }

    void twistCallback(const geometry_msgs::TwistStamped::ConstPtr& twist_msg) {
        latest_twist_ = *twist_msg;
        publishOdom();
    }

    void publishOdom() {
        // if (latest_pose_.header.stamp != latest_twist_.header.stamp) {
        //     return;  // 确保数据时间戳一致
        // }

        nav_msgs::Odometry odom_msg;
        odom_msg.header.stamp = latest_pose_.header.stamp;
        odom_msg.header.frame_id = "odom";  // 设置参考坐标系
        odom_msg.child_frame_id = "base_link";

        // 填充位置信息
        odom_msg.pose.pose = latest_pose_.pose;

        // 填充速度信息
        odom_msg.twist.twist = latest_twist_.twist;

        // 发布 Odom 消息
        odom_pub_.publish(odom_msg);
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "odom_publisher");
    OdomPublisher odom_publisher;
    ros::spin();
    return 0;
}

