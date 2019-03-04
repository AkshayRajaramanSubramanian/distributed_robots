#ifndef SUBSCRIBE_POSITION_H
#define SUBSCRIBE_POSITION_H

#include "ros/ros.h"
#include <boost/bind.hpp>
#include <distributed_robots/RobotPose.h>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

using namespace std::chrono;

bool compareFuncDistance (distributed_robots::RobotPose a, distributed_robots::RobotPose b) {
  return sqrt(pow(a.x, 2) + pow(a.y, 2)) < sqrt(pow(b.x, 2) + pow(b.y, 2));
}

class SubscribePosition {
  public :
    SubscribePosition();
    ~SubscribePosition();
    void findNeighbors();
    void displayPosition();

  private :
    ros::NodeHandle nh;
    std::vector<ros::Subscriber> sub_robot_pose;
    int total_robots;
    std::vector<distributed_robots::RobotPose> robot_poses;

    void positionCallback(const distributed_robots::RobotPoseConstPtr& msg);
};

#endif
