#include "simpletools.h"          // Include simpletools library
#include "abdrive360.h"           // Include abdrive360 library

int main()                        // Main function
{
  drive_speed(64, 64);            // Set both motors to move forward at a speed of 64
  pause(2000);                    // Wait for 2 seconds
  drive_speed(-32, -32);          // Set both motors to move backward at a speed of 32
  pause(1000);                    // Wait for 1 second
  drive_speed(0, 0);              // Stop both motors
  return 0;                       // End of the main function
}

