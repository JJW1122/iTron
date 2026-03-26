#include "rclcpp/rclcpp.hpp" // Include the ROS 2 C++ client library
#include "std_msgs/msg/int32.hpp" // Include the standard Int32 message type  
#include <chrono> // Include the chrono library for timing

using namespace std::chrono_literals; // Use the chrono literals for easier time handling

//namespace for our publisher node

class NumberPublisher : public rclcpp::Node // Define a class that inherits from rclcpp::Node
{
public:
    NumberPublisher() : Node("number_publisher"), count_(0) {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("count_topic", 10); // Create a publisher that publishes Int32 messages to the "number_topic" with a queue size of 10
        timer_ = this->create_wall_timer(1000ms, [this]() {timer_callback();}); // Create a timer that calls the timer_callback function every 1000 milliseconds (1 second)
    }   
private:        
    void timer_callback() {
        auto message = std_msgs::msg::Int32(); // Create a new Int32 message
        message.data = count_++;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data); // Log the published message
        publisher_->publish(message); // Publish the message
    }   

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_; // Declare a shared pointer for the publisher    
    rclcpp::TimerBase::SharedPtr timer_; // Declare a shared pointer for the timer

    int count_; // Declare a counter variable to keep track of the number being published
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv); // Initialize the ROS 2 system
    rclcpp::spin(std::make_shared<NumberPublisher>()); // Create an instance of the NumberPublisher class and spin it to process callbacks
    rclcpp::shutdown(); // Shutdown the ROS 2 system when done
    return 0; // Return 0 to indicate successful execution
}   