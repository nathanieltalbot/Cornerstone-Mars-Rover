# Cornerstone-Mars-Rover
This is an arduino-based project for GE 1502 Cornerstone of Engineering 2 at Northeastern University. 
The project is running using Sparkfun Weather Shield, MQ-3 Alcohol Sensor, Sparkfun LCD Readout, as well as three separate servo motors and an IR sensor, able to receive IR input from a standard TV remote.

The Sensor_Code.ino sketch is solely for reading data from the sensors on the Weather Shield and the MQ-3 sensor. The Full_Rover_Code.ino sketch is the full sketch for robot operation

The Sparkfun RedBoard Pinout is as follows:


| Pin | Usage                 |
|-----|-----------------------|
| A0  | B1 Pin on MQ-3 Sensor |
| A1  | Light Sensor          |
| A2  | None                  |
| A3  | 3V3 Reference         |
| A4  | None                  |
| A5  | None                  |
| 2   | None                  |
| 3   | None                  |
| 4   | None                  |
| 5   | None                  |
| 6   | Motor R               |
| 7   | Motor L               |
| 8   | Scoop Servo           |
| 9   | IR Sensor             |
| 10  | SD Shield CS          |
| 11  | SD Shield DI          |
| 12  | SD Shield DO          |
| 13  | SD Shield CLK         |