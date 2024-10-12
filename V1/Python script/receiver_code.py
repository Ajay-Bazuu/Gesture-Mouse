import serial
import pyautogui

# Open the serial port (replace 'COM3' with the correct port for your system)
ser = serial.Serial('COM3', 115200)  # On Windows, use 'COMx', on Linux/Mac use '/dev/ttyUSBx'

# Infinite loop to continuously read serial data
while True:
    try:
        # Read data from serial and decode it
        data = ser.readline().decode('utf-8').strip()
        if data:
            # Split the received data into x and y components
            x, y = map(int, data.split(','))

            # Move the mouse based on the received values
            pyautogui.moveRel(x, -y, duration=0.01)  # -y is used to correct the axis if inverted
    except:
        pass
