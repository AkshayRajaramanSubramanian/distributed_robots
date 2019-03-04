#include "subscriber.hpp"

SubscribePosition::SubscribePosition() {
  nh.getParam("/no_of_robots", total_robots);

  for (int i = 0; i < total_robots; i++) {
    distributed_robots::RobotPose robot_pose;
    robot_pose.id = i;
    robot_pose.x = 0;
    robot_pose.y = 0;
    robot_poses.push_back(robot_pose);
  }

  for (int i = 0; i < total_robots; i++) {
    sub_robot_pose.push_back(nh.subscribe<distributed_robots::RobotPose>
            ("/robot_" + std::to_string(i), 1, &SubscribePosition::positionCallback, this));
  }
}

SubscribePosition::~SubscribePosition() {}

void SubscribePosition::positionCallback(const distributed_robots::RobotPoseConstPtr& msg) {
   //std::cout << "Id : " << msg->id << "\n";
   robot_poses[msg->id].x = msg->x;
   robot_poses[msg->id].y = msg->y;
}

void SubscribePosition::findNeighbors() {
  std::sort(robot_poses.begin(), robot_poses.end(), compareFuncDistance);
}

void SubscribePosition::displayPosition() {
  for (int i = 0; i < total_robots; i++) {
    std::cout << "Robot " << i << " Pose : " << robot_poses[i].x << " " << robot_poses[i].y << " " << sqrt(pow(robot_poses[i].x, 2) + pow(robot_poses[i].y, 2)) << "\n";
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_position_subscribe");
  SubscribePosition *node = new SubscribePosition();
  ros::Rate *rate = new ros::Rate(20);

  while (ros::ok()){
    auto start = high_resolution_clock::now();
    rate->sleep();
    ros::AsyncSpinner spinner(100);
    spinner.start();
    node->findNeighbors();
    //node->displayPosition();
    auto end = high_resolution_clock::now();
    std::cout << " Total time : " << duration_cast<microseconds>(end - start).count() << "\n\n";
  }

  return 0;
}
