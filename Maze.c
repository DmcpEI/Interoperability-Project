/* Code from Sprint 2

#include "abdrive360.h"
#include "ping.h"

int main() {
  while (!input(0)) {
    pause(10);
  }

  drive_speed(64, 64);

  while (1) {
    if (ping_cm(8) > 10) { 
      drive_speed(64, 64);
    } else {
      drive_speed(0, 0);
      drive_goto(-26, 26);
      if (ping_cm(8) > 10) {
        drive_speed(64, 64);
      } else if (ping_cm(8) <= 10) {
        drive_goto(-52, -52);
        if (ping_cm(8) > 10) {
          drive_speed(64, 64);
        } else {
          drive_goto(26, -26);
        }
      }
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

  // Main loop
  while (1) {
    // Drive for 1 second
    drive_speed(64, 64); // Move forward at 64 speed
    pause(1000); // Wait for 1 second
    drive_ramp(0, 0); // Stop the robot
    pause(100); // Delay to ensure the robot has stopped

    // Check surroundings
    int frontDistance = ping_cm(8); // Distance in front

    // Rotate to check the right side
    drive_goto(-26, 26); // Turn right by 150 degrees
    int rightDistance = ping_cm(8); // Distance on the right
    drive_ramp(0, 0); // Stop the robot
    pause(100); // Delay to ensure the robot has stopped

    // Rotate to check the left side
    drive_goto(52, -52); // Turn left by 300 degrees
    int leftDistance = ping_cm(8); // Distance on the left
    drive_ramp(0, 0); // Stop the robot
    pause(100); // Delay to ensure the robot has stopped

    // Rotate back to the original orientation
    drive_goto(-26, 26); // Turn right by 150 degrees

    // Debug output
    print("Front distance: %d cm\n", frontDistance);
    print("Right distance: %d cm\n", rightDistance);
    print("Left distance: %d cm\n", leftDistance);

    // Choose the best way to go based on the detected walls
    if (frontDistance > 10) { // If no wall in front
      // Go straight
      print("Going straight\n");
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop the robot
      pause(100); // Delay to ensure the robot has stopped
    } else if (rightDistance > 10) { // If no wall on the right
      // Turn right
      print("Turning right\n");
      drive_goto(-26, 26); // Turn right by 150 degrees
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop the robot
      pause(100); // Delay to ensure the robot has stopped
    } else if (leftDistance > 10) { // If no wall on the left
      // Turn left
      print("Turning left\n");
      drive_goto(26, -26); // Turn left by 150 degrees
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop the robot
      pause(100); // Delay to ensure the robot has stopped
    } else {
      // Dead-end, turn around
      print("Dead-end, turning around\n");
      drive_goto(52, -52); // Turn around by 360 degrees
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop
    }
  }    
  return 0;
}          

