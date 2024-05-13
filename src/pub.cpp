#include "psub2-2/pub.hpp"
using namespace std;
Pub::Pub() : Node("mypub"), count_(0)
{
auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("mytopic", qos_profile);
timer_ = this->create_wall_timer(1s, std::bind(&Pub::publish_msg, this));
}
void Pub::publish_msg()
{
    while (rclcpp::ok()) {
        geometry_msgs::msg::Vector3 msg;        
        cout << "insert any numbers: ";
        cin >> msg.x >> msg.y >> msg.z;        
        pub_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "R msg: %lf %lf %lf", msg.x, msg.y, msg.z);
        std::function<void()> fn = std::bind(&Pub::publish_msg, this);
        timer_ = this->create_wall_timer(1s, fn);
        //rclcpp::spin_some(node);
        //loop_rate.sleep();
    }
}
