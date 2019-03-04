#ifndef PUBLISH_POSITION_H
#define PUBLISH_POSITION_H

#include "ros/ros.h"
#include <distributed_robots/RobotPose.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std::chrono;

class PublishPosition {
  public :
    PublishPosition();
    ~PublishPosition();
    void threadPublisher();

  private:
    ros::NodeHandle nh;
    std::vector<ros::Publisher> pub_robot_pose;
    int total_robots;
    std::mutex mtx;

    std::vector<double> fetchPosition();
    void publishRobotPose(int i);
};

#endif
