#include <Wire.h>
#include <MadgwickAHRS.h>
#include <MPU6050.h>

Madgwick filter;
MPU6050 mpu;

float sensitivity = 0.8;     // Adjust sensitivity for mouse movement
float moveThreshold = 0.05;  // Ignore small movements

// Variables to store the initial roll and pitch
float initialRoll = 0;
float initialPitch = 0;
void setup() {
  Serial.begin(115200);  // Initialize Serial communication
  Wire.begin();
  mpu.initialize();
  filter.begin(100);  // Filter update rate in Hz
  Serial.println("MPU6050 Mouse Control Ready");

  // Wait for the sensor to stabilize
  delay(1000);
  initialCalculation();
}
void loop() {
  finalCalculation();
}


void initialCalculation() {
  // Variables to accumulate multiple readings
  float totalRoll = 0;
  float totalPitch = 0;
  const int numReadings = 10;  // Number of readings to average

  for (int i = 0; i < numReadings; i++) {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float gyroX = gx / 131.0;
    float gyroY = gy / 131.0;
    float gyroZ = gz / 131.0;
    float accelX = ax / 16384.0;
    float accelY = ay / 16384.0;
    float accelZ = az / 16384.0;

    filter.updateIMU(gyroX, gyroY, gyroZ, accelX, accelY, accelZ);

    // Accumulate roll and pitch values
    totalRoll += filter.getRoll();
    totalPitch += filter.getPitch();

    // Delay between readings (optional, to allow for stabilization)
    delay(100);
  }

  // Calculate the average roll and pitch
  initialRoll = totalRoll / numReadings;
  initialPitch = totalPitch / numReadings;
  Serial.println("Initial roll and pitch set based on average of readings.");

  Serial.println(initialRoll);
  Serial.println(initialPitch);
  delay(1000);
}
void finalCalculation() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  // Serial.println(ax);
  // Serial.println(ay);
  // Serial.println(az);
  // Serial.println(gx);
  // Serial.println(gy);
  // Serial.println(gz);
  // Convert raw values to degrees/s and g's
  float gyroX = gx / 131.0;
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  // Update the Madgwick filter with gyroscope and accelerometer data
  filter.updateIMU(gyroX, gyroY, gyroZ, accelX, accelY, accelZ);

  // Get orientation angles (in radians)
  float roll = filter.getRoll();
  float pitch = filter.getPitch();

  // Subtract the initial roll and pitch to make the current position relative to the start
  float relativeRoll = roll - initialRoll;
  float relativePitch = pitch - initialPitch;

  // Scale the movement for smooth cursor control
  int moveX = relativeRoll * sensitivity;   // Scale factor to adjust movement
  int moveY = relativePitch * sensitivity;  // Scale factor to adjust movement

  // Ignore movements between -10 and 10
  if (moveX >= -1 && moveX <= 1) {
    moveX = 0;  // Set moveX to 0 if it's within the range
  }
  if (moveY >= -1 && moveY <= 1) {
    moveY = 0;  // Set moveY to 0 if it's within the range
  }

  // Print the values if there's a significant movement
  if (abs(moveX) > moveThreshold || abs(moveY) > moveThreshold) {
    Serial.print("MoveX: ");  // Print X movement data
    Serial.print(moveX);
    Serial.print(", MoveY: ");  // Print Y movement data
    Serial.println(moveY);
  }
  delay(110);  // Adjust delay as needed
}
