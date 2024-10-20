import pyautogui
import serial
import time

# Replace 'COM4' with the correct port for your setup
ser = serial.Serial('COM4', 115200)  # Open serial port
time.sleep(2)  # Wait for the serial connection to initialize
# movement_threshold=8
sensivity=15

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()  # Read the data
        print(line)  # Print the received data

        # Check if the line contains the expected format
        if "MoveX:" in line and "MoveY:" in line:
            try:
                move_data = line.split(', ')
                
                # Validate the received data
                if len(move_data) == 2:  # Ensure there are two elements
                    moveX = int(move_data[0].split(': ')[1]) * sensivity# 10 for increasing the sensitivity
                    moveY = int(move_data[1].split(': ')[1]) * sensivity

                    # Get the current mouse position
                    current_x, current_y = pyautogui.position()

                    # Calculate new cursor position
                    new_x = current_x + moveX
                    new_y = current_y + moveY

                    # Ensure the cursor stays within screen bounds
                    screen_width, screen_height = pyautogui.size()
                    new_x = max(0, min(new_x, screen_width - 1))  # Limit to screen width
                    new_y = max(0, min(new_y, screen_height - 1))  # Limit to screen height
                    
                    # if abs(moveX)<movement_threshold and abs(moveY)<movement_threshold:
                        # Move the cursor to the new position
                    pyautogui.moveTo(new_x, new_y)
                
                    time.sleep(0.05)
            except Exception as e:
                print("Error processing data:", e)
        else:
            print("Received malformed data:", line)  # Log if data is not as expected
