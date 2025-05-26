import os
import serial

SERIAL_PORT = '/dev/ttyACM0'
print("Exists?", os.path.exists(SERIAL_PORT))

if os.path.exists(SERIAL_PORT):
    ser = serial.Serial(SERIAL_PORT, 9600)
    print("Connected.")
    print("Reading line...")
    print(ser.readline())
else:
    print("Serial port not found.")