import socket
import cv2
import numpy as np

# --- Setup UDP socket ---
arduino_ip = '172.20.10.4'  # Replace with your Arduino's IP address
arduino_port = 2390           # Must match Arduino sketch
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def send_command(command):
    try:
        sock.sendto(command.encode(), (arduino_ip, arduino_port))
        print(f"Sent command: {command}")
    except Exception as e:
        print(f"Error sending command: {e}")

# --- OpenCV camera setup ---
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Could not open camera.")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to read frame.")
        break

    frame_width = frame.shape[1]
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # # Pink color range
    # lower_pink = np.array([160, 80, 100])
    # upper_pink = np.array([175, 255, 255])
    # mask = cv2.inRange(hsv, lower_pink, upper_pink)

    # yellow color range
    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([30, 255, 255])
    mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

    # Morphological filtering
    kernel = np.ones((5, 5), np.uint8)
    mask = cv2.erode(mask, kernel, iterations=1)
    mask = cv2.dilate(mask, kernel, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    direction = "S"  # Default to stop

    if contours:
        largest = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(largest)

        frame_area = frame.shape[0] * frame.shape[1]
        object_area = w * h
        fill_ratio = object_area / frame_area

        # Debug
        print(f"Fill ratio: {fill_ratio:.2f}")

        if fill_ratio > 0.3:
            direction = "S"
            send_command("Too Close")
            print("TOO CLOSE — Stopping")
        else:
            center_x = x + w // 2

            if center_x < frame_width / 4:
                direction = "L"
            elif center_x > 2 * frame_width / 4:
                direction = "R"
            else:
                direction = "F"

        send_command(direction)

        # Display info on screen
        cv2.putText(frame, f"Dir: {direction}  Fill: {fill_ratio:.2f}", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    else:
        print("No yellow object detected")
        send_command("S")
        cv2.putText(frame, "No yellow detected", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

    # Show output
    cv2.imshow("Pink Mask", mask)
    cv2.imshow("Camera", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# On quit — stop the robot
send_command("S")
print("Sent stop command before exit.")

# Cleanup
cap.release()
cv2.destroyAllWindows()
