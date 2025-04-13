import cv2
import numpy as np
import serial
import time

# Change to your actual COM port (check Arduino IDE -> Tools -> Port)
ser = serial.Serial('COM5', 9600)
time.sleep(2)  # Let the serial connection settle

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([30, 255, 255])
    mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    direction = "S"  # Default to Stop

    if contours:
        largest = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(largest)
        center_x = x + w // 2

        frame_width = frame.shape[1]

        if center_x < frame_width / 3:
            direction = "L"  # Turn Left
        elif center_x > 2 * frame_width / 3:
            direction = "R"  # Turn Right
        else:
            direction = "F"  # Move Forward

        print(f"Sending: {direction}")
        ser.write(direction.encode())  # Send the command to Arduino
        time.sleep(0.05)

    else:
        print("No yellow object detected")
        ser.write(b"S")  # Send Stop

    cv2.imshow("Yellow Mask", mask)
    cv2.imshow("Camera", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
ser.close()
cv2.destroyAllWindows()
