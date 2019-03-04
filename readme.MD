# Distributed Robots

To start testing run `roscore` and then set the number of robot topics to be spawned using

```
rosparam set /no_of_robots 100
```

To publish the robot's position

```
rosrun distributed_robots publish_positions
```

And to subscribe and find neighbors

```
rosrun distributed_robots subscribe_positions
```
