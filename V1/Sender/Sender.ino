#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int x, y;

void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(115200);  // Start serial communication at 115200 baud rate

  // Initialize the MPU6050
  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  // Check if the MPU6050 is connected properly
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1);  // Stop the program if the connection fails
  }

  // Optional: Set specific configurations (accelerometer range, etc.)
  // mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);  // Set accelerometer sensitivity to ±2g (default)
}

void loop() {
  int16_t ax, ay, az;
  
  // Read the accelerometer values
  mpu.getAcceleration(&ax, &ay, &az);

  // Map the accelerometer data from -17000 to 17000 to a small range for smoother mouse control
  x = map(ax, -17000, 17000, -20, 20);  // Adjust -10 to 10 for sensitivity
  y = map(ay, -17000, 17000, -20, 20);  // Adjust -10 to 10 for sensitivity

  // Send x and y values to the serial port
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);

  delay(5);  // Add a delay for smoother movement
}
