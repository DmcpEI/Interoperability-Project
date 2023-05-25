#include "abdrive360.h" // Include the ActivityBot360 library
#include "ping.h"
#include <stdio.h>

#define MAX_SIZE 12 // Maximum maze size (should be odd)

void printMaze(char maze[][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%c ", maze[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int x = 0;
  int y = 0;
  int mazeSize = MAX_SIZE; // Maze size
  char maze[MAX_SIZE][MAX_SIZE]; // Matrix to represent the maze

  // Initialize the maze with walls
  for (int i = 0; i < mazeSize; i++) {
    for (int j = 0; j < mazeSize; j++) {
      if (i == 0 || i == mazeSize - 1 || j == 0 || j == mazeSize - 1) {
        maze[i][j] = '#'; // Borders
      } else {
        maze[i][j] = ' '; // Empty spaces inside the maze
      }
    }
  }

  // Main loop
  while (1) {
    // Update the robot's position in the maze
    maze[y + mazeSize/2][x + mazeSize/2] = '*';

    // Check surroundings
    int frontDistance = ping_cm(8); // Distance in front

    // Rotate to check the right side
    drive_goto(-26, 26); // Turn right 150 degrees
    int rightDistance = ping_cm(8); // Distance to the right
    drive_ramp(0, 0); // Stop the robot
    pause(100); // Delay to ensure the robot has stopped

    // Rotate to check the left side
    drive_goto(52, -52); // Turn left 300 degrees
    int leftDistance = ping_cm(8); // Distance to the left
    drive_ramp(0, 0); // Stop the robot
    pause(100); // Delay to ensure the robot has stopped

    // Rotate back to the original orientation
    drive_goto(-26, 26); // Turn right 150 degrees

    // Debug output
    printf("Front distance: %d cm\n", frontDistance);
    printf("Right distance: %d cm\n", rightDistance);
    printf("Left distance: %d cm\n", leftDistance);
    printf("X: %d\n", x);
    printf("Y: %d\n", y);

    // Check if the robot reached the end of the maze
    if (frontDistance > 20 && rightDistance > 20 && leftDistance > 20) {
      printf("Maze completed!\n");
      break; // Exit the loop
    }
    // Choose the best way to go based on the detected walls
    else if (frontDistance > 10) { // If there is no wall in front
      // Go straight
      printf("Going straight\n");
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop the robot
      pause(100); // Delay to ensure the robot has stopped
      y = y + 1;
    } else if (rightDistance > 10) { // If there is no wall to the right
      // Turn right
      printf("Turning right\n");
      drive_goto(-26, 26); // Turn right 150 degrees
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop the robot
      pause(100); // Delay to ensure the robot has stopped
      x = x + 1;
    } else if (leftDistance > 10) { // If there is no wall to the left
      // Turn left
      printf("Turning left\n");
      drive_goto(26, -26); // Turn left 150 degrees
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop the robot
      pause(100); // Delay to ensure the robot has stopped
      x = x - 1;
    } else {
      // Dead-end, turn around
      printf("Dead-end, turning around\n");
      drive_goto(52, -52); // Turn 360 degrees
      drive_speed(64, 64);
      pause(1000); // Drive for 1 second
      drive_ramp(0, 0); // Stop
      y = y - 1;
    }
  }

  // Print the maze map
  printMaze(maze, mazeSize);

  return 0;
}
