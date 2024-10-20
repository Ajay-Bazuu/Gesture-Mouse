import pyautogui
import time

# Move the mouse to coordinates (100, 100)
pyautogui.moveTo(100, 100)
print("Cursor moved")
time.sleep(1)
# Click at the current mouse position
pyautogui.click()
print("Clicked ")
time.sleep(1)
# Right-click at position (200, 300)
pyautogui.rightClick(200, 300)
print("right clicked")
time.sleep(1)

# Drag the mouse to a different position (500, 500) over 2 seconds
pyautogui.dragTo(500, 500, duration=2)
print("Drag to")
time.sleep(1)