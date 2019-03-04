#include "publisher.hpp"

PublishPosition::PublishPosition() {
  nh.getParam("/no_of_robots", total_robots);

  for (int i = 0; i < total_robots; i++) {
    pub_robot_pose.push_back(nh.advertise<distributed_robots::RobotPose>("/robot_" + std::to_string(i), 1000));
  }
}

PublishPosition::~PublishPosition() {}

void PublishPosition::publishRobotPose(int i) {
  std::vector<double> pose = fetchPosition();
  distributed_robots::RobotPose robot_pose;
  robot_pose.id = i;
  robot_pose.x = pose[0];
  robot_pose.y = pose[1];
  pub_robot_pose[i].publish(robot_pose);
}

void PublishPosition::threadPublisher() {
  //std::vector<boost::thread*> thread_list;
  auto start = high_resolution_clock::now();
  for (int i = 0; i < total_robots; i++) {
    publishRobotPose(i);
    //boost::thread* thr = new boost::thread(boost::bind(&PublishPosition::publishRobotPose, this, i));
    //thread_list.push_back(thr);
  }
  //for (boost::thread* thr: thread_list){ thr->join(); }
  auto end = high_resolution_clock::now();
  std::cout << " Total time : " << duration_cast<microseconds>(end - start).count() << "\n\n";
}

std::vector<double> PublishPosition::fetchPosition() {
  std::vector<double> pose;
  std::default_random_engine eng((std::random_device())());
  std::uniform_real_distribution<double> ddis(0, 10.0);
  std::uniform_int_distribution<int> idis(0, 2);
  pose.push_back(ddis(eng));
  pose.push_back(ddis(eng));
  return pose;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_position_publisher");
  PublishPosition *node = new PublishPosition();
  ros::Rate *rate = new ros::Rate(20);

  while (ros::ok()){
    node->threadPublisher();
    rate->sleep();
  }

  return 0;
}
