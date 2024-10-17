import pyautogui
import serial
import time

# Replace 'COM3' with the correct port for your setup
ser = serial.Serial('COM4', 115200)  # Open serial port
time.sleep(2)  # Wait for the serial connection to initialize

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()  # Read the data
        print(line)  # Print the received data
        # Example format: "MoveX: 50, MoveY: -30"
        try:
            move_data = line.split(', ')
            moveX = int(move_data[0].split(': ')[1])
            moveY = int(move_data[1].split(': ')[1])

            # Get the current mouse position
            current_x, current_y = pyautogui.position()

            # Calculate new cursor position
            new_x = current_x + moveX
            new_y = current_y + moveY

            # Ensure the cursor stays within screen bounds
            screen_width, screen_height = pyautogui.size()
            new_x = max(0, min(new_x, screen_width - 1))  # Limit to screen width
            new_y = max(0, min(new_y, screen_height - 1))  # Limit to screen height

            # Move the cursor to the new position
            pyautogui.moveTo(new_x, new_y)

        except Exception as e:
            print("Error processing data:", e)
