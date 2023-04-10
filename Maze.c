/*
#include "abdrive360.h"
#include "ping.h"


int main()
{
  drive_speed(64, 64);  // set the initial speed of the robot
  while(1) {
    if (ping_cm(8) < 10) {  // check if there's an obstacle within 10 cm in front of the robot
      drive_speed(0, 0);   // stop the robot
      drive_goto(26, -25); // turn left
      drive_speed(64, 64); // continue moving forward
    } else if (ping_cm(10) < 10) { // check if there's an obstacle within 10 cm on the left side of the robot
      drive_speed(0, 0);  // stop the robot
      drive_goto(13, 13); // move forward a bit to get away from the wall
      drive_goto(25, 26); // turn right
      drive_speed(64, 64); // continue moving forward
    } else if (ping_cm(2) < 10) { // check if there's an obstacle within 10 cm on the right side of the robot
      drive_speed(0, 0);  // stop the robot
      drive_goto(13, 13); // move forward a bit to get away from the wall
      drive_goto(-25, -26); // turn left
      drive_speed(64, 64); // continue moving forward
    } else { // if there's no obstacle, just continue moving forward
      drive_speed(64, 64);
    }
  }
  return 0;
}
*/

#include "abdrive360.h" // Include the ActivityBot360 library
#include "ping.h"

int main() {
  // Wait for the RST button to be pressed
  while (!input(0)) {
    pause(10);
  }

  // Initialize the ActivityBot360
  drive_speed(64, 64); // Move forward at 64 speed

  // Follow the maze using the ultrasonic sensor
  while (1) {
    if (ping_cm(8) > 10) { // If there's no wall within 10 cm
      drive_speed(64, 64); // Move forward at 64 speed
    } else { // If there's a wall within 10 cm
      drive_speed(0, 0); // Stop the robot
      drive_goto(-26, 26); // Turn right by 150 degrees
      if (ping_cm(8) > 10) { // If there's no wall on the right within 10 cm
        drive_speed(64, 64); // Move forward at 64 speed
      } else if (ping_cm(8) <= 10) { // If there's a wall on the right within 10 cm
        drive_goto(-52, -52); // Turn around by 360 degrees
        if (ping_cm(8) > 10) { // If there's no wall behind within 10 cm
          drive_speed(64, 64); // Move forward at 64 speed
        } else { // If there's a wall behind within 10 cm
          drive_goto(26, -26); // Turn left by 150 degrees
        }
      }
    }
  }
  return 0;
}