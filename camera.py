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
        print("Failed to read frame.")
        break
    
    frame_width = frame.shape[1]
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([30, 255, 255])
    mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

    kernel = np.ones((5,5),np.uint8)
    mask = cv2.erode(mask, kernel, iterations=1)
    mask = cv2.dilate(mask, kernel, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    direction = "S"  # Default to Stop

    if contours:
        largest = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(largest)
        frame_area = frame.shape[0] * frame.shape[1]
        object_area = w * h
        fill_ratio = object_area / frame_area

        # Debugging info (optional)
        print(f"Fill ratio: {fill_ratio:.2f}")

        # Check if it's too close
        if fill_ratio > 0.3:  # 30% of the frame covered
            direction = "S"
            print("TOO CLOSE - Stopping")

            print(f"Sending: {direction}")
            ser.write(direction.encode())  # Send the command to Arduino
            time.sleep(0.05)
        else:
            center_x = x + w // 2

            if center_x < frame_width / 3:
                direction = "L"  # Turn Left
            elif center_x > 2 * frame_width / 3:
                direction = "R"  # Turn Right
            else:
                direction = "F"  # Move Forward

            print(f"Sending: {direction}")
            ser.write(direction.encode())  # Send the command to Arduino
            time.sleep(0.05)

            # Your normal left/right/forward logic goes here
            if x < frame_width // 2:
                direction = "L"
            elif x > frame_width // 2:
                direction = "R"
            else:
                direction = "F"

        frame_width = frame.shape[1]

    else:
        print("No yellow object detected")
        ser.write(b"S")  # Send Stop

    if 'fill_ratio' in locals():
        cv2.putText(frame, f"Fill: {fill_ratio:.2f}", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)


    cv2.imshow("Yellow Mask", mask)
    cv2.imshow("Camera", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Send stop command before exiting
try:
    ser.write(b'S')  # Stop motors
    print("Sent stop command to Arduino.")
except Exception as e:
    print(f"Couldn't send stop command: {e}")

cap.release()
ser.close()
cv2.destroyAllWindows()
