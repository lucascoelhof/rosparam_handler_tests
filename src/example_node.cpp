#include "ros/ros.h"
#include "std_msgs/String.h"

#include "rosparam_handler_tests/rosparamParameters.h"
#include "rosparam_handler_tests/rosparamConfig.h"
#include <dynamic_reconfigure/server.h>


#include <sstream>


class NodeClass
{
    private:
        dynamic_reconfigure::Server<rosparam_handler_tests::rosparamConfig> reconfigSrv;

    public:
        rosparam_handler_tests::rosparamParameters params;


    NodeClass() : params{ros::NodeHandle("~")}, reconfigSrv{ros::NodeHandle("~")}
    {
      params.fromParamServer();
      reconfigSrv.setCallback(boost::bind(&NodeClass::reconfigureRequest, this, _1, _2));
    }

    void reconfigureRequest(rosparam_handler_tests::rosparamConfig& config, uint32_t level) {
        params.fromConfig(config);
        ROS_WARN("Updated parameters");
    }
};



int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);

  NodeClass* nodeclass = new NodeClass();

  int count = 0;
  while (ros::ok())
  {

    std_msgs::String msg;

    int numnum = nodeclass->params.number_of_numbers;

    std::stringstream ss;
    for(int i=0; i < numnum; i++)
    {
        ss << i << " ";
    }

    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
