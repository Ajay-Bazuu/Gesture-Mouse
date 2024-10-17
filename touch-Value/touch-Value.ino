// Define the touch pin (T0 corresponds to GPIO 4)
#define TOUCH_PIN  4

void setup() {
  Serial.begin(115200);
  delay(1000); // Allow some time for serial communication to start
}

void loop() {
  // Read the value from the touch pin and print it
  int touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);

  delay(500); // Wait for 500 milliseconds before the next reading
}
