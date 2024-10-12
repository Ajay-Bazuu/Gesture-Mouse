#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int x, y;

void setup() {
  Wire.begin();
  mpu.initialize();
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Map the accelerometer data from -17000 to 17000 to a small range for smoother mouse control
  x = map(ax, -17000, 17000, -10, 10);  // Change -10 to 10 for sensitivity
  y = map(ay, -17000, 17000, -10, 10);  // Change -10 to 10 for sensitivity

  // Send x and y values to the serial port
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);

  delay(50);  // Add a delay for smoother movement
}
 