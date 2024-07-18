# Your Robot

This robot is for autonomous sumo robot competition for the weight class 1 kg. 

This robot has 7 sensors, 2 DC motors (12 V & 130 rpm) controlled by Arduino Nano and powered by 11.1 V Li-Ion battery.

The robot can be programmed by connecting the programming environment (Arduino IDE) to Arduino Board by using USB C-to-C cable.

The USB C port of Arduino Board can be accessed from the back of the robot.

The battery can be charged by using USB adapter to white port of the battery. It recommended for the operator to prepare a powerbank for charging the robot during a competition.

To run the robot, turn the black switch on, and press one of the button.

The routine of each button is as follows:

| Button  | Initial Wait (s) | Initial Position | Initial Motion | Competition |
| ------------- | :---: | :---: | :---: | :---: |
| S1  | 5 | Facing Opponent| Attacking straight | RBTX | 
| S2  | 5 | Facing Operator/ Side | 180° | RBTX / UNIKL | 
| S3  | 3 | Facing Operator | 180° | IRC |
| S4  | 5 | Facing Opponent| Attacking straight | RBTX |
