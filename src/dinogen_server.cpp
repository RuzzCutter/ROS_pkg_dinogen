#include "ros/ros.h"
#include "std_msgs/String.h"
#include "dinogen/Dinogen.h"
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>

bool serviceCallback(dinogen::Dinogen::Request  &req,
         dinogen::Dinogen::Response &res)
{
  std::vector<std::string> dinos = {
    "saurus", "raptor", "pteryx", "stacator", "rex", "ceratops", "gnathus",
    "roides", "draco", "dromeus", "bator"};
  std::string input = req.word;
  if (!input.empty()){
    input[0] = std::toupper(input[0]);
  }
  std::srand(static_cast<unsigned int>(std::time(0)));
  int rndIndex = std::rand() % dinos.size();
  res.dinoname = input + dinos[rndIndex];
  ros::NodeHandle nh;
  ros::Publisher dino_pub = nh.advertise<std_msgs::String>("dino_pub", 10);
  std_msgs::String msg;
  std::stringstream ss;
  ss << res.dinoname;
  msg.data = ss.str();
  dino_pub.publish(msg);
  return true;
}

void topicCallback(const std_msgs::String::ConstPtr& msg)
{
  std::vector<std::string> families = {
    "Theropods", "Sauropodomorphs", "Stegosauridae", "Ceratopsidae", 
    "Hadrosauridae", "Ankylosauridae", "Iguanodontidae"};
  int rndIndexFml = std::rand() % families.size();
  std::vector<std::string> periods = {
    "Early", "Middle", "Late"};
  int rndIndexPrd = std::rand() % periods.size();
  
  ROS_INFO("%s belonged to the %s family and lived in the %s Triassic.", 
  msg->data.c_str(), families[rndIndexFml].c_str(), periods[rndIndexPrd].c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dinogen_server");
  ros::NodeHandle nh;

  ros::Publisher dino_pub = nh.advertise<std_msgs::String>("dino_pub", 10);
  ros::Subscriber dino_sub = nh.subscribe("dino_pub", 10, topicCallback);

  ros::ServiceServer service = nh.advertiseService("dinogen_service", serviceCallback);
    
  ros::spin();

  return 0;
}