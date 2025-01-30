#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>

#define TIME_STEP 64
#define MAX_POSITION 0.15
#define MIN_POSITION 0.0
#define SPEED 0.08

int main() {
  wb_robot_init();

  // Print available devices
  int device_count = wb_robot_get_number_of_devices();
  printf("Number of devices: %d\n", device_count);
  for (int i = 0; i < device_count; i++) {
    WbDeviceTag device = wb_robot_get_device_by_index(i);
    // For devices like motors, there isn't a direct 'name' you can fetch this way
    printf("Device %d: %d\n", i, device);  // Print the device tag (which represents the device)
  }

  // Get the correct motor name
  WbDeviceTag linear_motor = wb_robot_get_device("linearmotor");  
  if (linear_motor == 0) {
    printf("Error: Motor 'linear motor' not found! Use a correct device name.\n");
    wb_robot_cleanup();
    return -1;
  }

  // Set velocity for motion
  wb_motor_set_velocity(linear_motor, SPEED);
  wb_motor_set_position(linear_motor, MIN_POSITION);

  double target_position = MAX_POSITION;

  while (wb_robot_step(TIME_STEP) != -1) {
    double current_position = wb_motor_get_target_position(linear motor);

    if (current_position >= MAX_POSITION) {
      target_position = MIN_POSITION;
    } else if (current_position <= MIN_POSITION) {
      target_position = MAX_POSITION;
    }

    wb_motor_set_position(linear_motor, target_position);
  }

  wb_robot_cleanup();
  return 0;
}
