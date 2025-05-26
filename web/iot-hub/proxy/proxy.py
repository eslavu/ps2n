from flask import Flask, jsonify, request
import serial
import threading
import time
from azure.iot.hub import IoTHubRegistryManager
import os

import smtplib
from email.mime.text import MIMEText
from datetime import datetime, timedelta

app = Flask(__name__)

SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 9600
ser = None

IOTHUB_CONNECTION_STRING = os.getenv('IOTHUB_CONNECTION_STRING')
DEVICE_ID = os.getenv('DEVICE_ID')

if not IOTHUB_CONNECTION_STRING or not DEVICE_ID:
    raise Exception("Please set IOTHUB_CONNECTION_STRING and DEVICE_ID environment variables")

registry_manager = IoTHubRegistryManager(IOTHUB_CONNECTION_STRING)

EMAIL_FROM = os.getenv('PS2_EMAIL_FROM')
EMAIL_TO = os.getenv('PS2_EMAIL_TO')
EMAIL_SUBJECT = 'Flood Detected'
EMAIL_SMTP_SERVER = 'smtp.gmail.com'
EMAIL_SMTP_PORT = 587
EMAIL_USERNAME = os.getenv('PS2_EMAIL_FROM')
EMAIL_PASSWORD = os.getenv('PS2_EMAIL_PASSWORD')

last_email_time = datetime.min
EMAIL_COOLDOWN = timedelta(hours=1)

data = {
    'temperature': None,
    'humidity': None,
    'system_state': False,
    'flood_level': None,
    'heat_level': None
}

def flood_email(humidity):
    global last_email_time
    now = datetime.now()
    if now - last_email_time < EMAIL_COOLDOWN:
        print("Cooldown active, email not sent.")
        return

    body = f"A flood condition was detected.\n\nHumidity: {humidity:.1f}%"
    msg = MIMEText(body)
    msg['Subject'] = EMAIL_SUBJECT
    msg['From'] = EMAIL_FROM
    msg['To'] = EMAIL_TO

    try:
        with smtplib.SMTP(EMAIL_SMTP_SERVER, EMAIL_SMTP_PORT) as server:
            server.starttls()
            server.login(EMAIL_USERNAME, EMAIL_PASSWORD)
            server.send_message(msg)
        print(f"Flood alert email sent to {EMAIL_TO}")
        last_email_time = now
    except Exception as e:
        print(f"Error sending email: {e}")

def get_flood_level(humidity):
    if humidity < 40:
        return 0
    elif humidity < 50:
        return 1
    else:
        flood_email(humidity)
        return 2

def get_heat_level(temp):
    if temp < 15:
        return 0
    elif temp < 26:
        return 1
    else:
        return 2

def connect_serial():
    global ser
    while ser is None:
        try:
            ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
            print(f"Connected to {SERIAL_PORT}")
        except Exception as e:
            print(f"Error connecting serial: {e}")
            time.sleep(3)

def read_serial():
    global data, ser
    
    while True:
        if ser is None:
            connect_serial()
            continue
        try:
            line = ser.readline().decode('utf-8').strip()
            
            if line:
                print(f"Serial data: {line}")
                parts = line.split(',')
                if len(parts) >= 2:
                    if data['system_state']:
                        temp_part = parts[0].split(':')
                        hum_part = parts[1].split(':')
                        if temp_part[0] == 'temp' and hum_part[0] == 'hum':
                            try:
                                temperature = float(temp_part[1])
                                humidity = float(hum_part[1])
                            except ValueError:
                                continue

                            data['temperature'] = temperature
                            data['humidity'] = humidity

                            flood = get_flood_level(humidity)
                            heat = get_heat_level(temperature)
                            data['flood_level'] = flood
                            data['heat_level'] = heat

                            message = f"{flood},{heat}\n"
                            ser.write(message.encode())

                        try:
                            twin_patch = {
                                "properties": {
                                    "reported": {
                                        "temperature": temperature,
                                        "humidity": humidity,
                                        "system_state": data['system_state'],
                                        "flood_level": flood,
                                        "heat_level": heat
                                    }
                                }
                            }
                            registry_manager.update_twin(DEVICE_ID, twin_patch, "*")
                        except Exception as e:
                            print(f"Error updating IoT Hub twin: {e}")

        except Exception as e:
            print(f"Serial read error: {e}")
            if ser:
                ser.close()
            ser = None
            time.sleep(3)

@app.route('/data', methods=['GET'])
def get_data():
    return jsonify(data)

@app.route('/command', methods=['POST'])
def send_command():
    global ser, data
    cmd = request.json.get('command')
    if cmd not in ['ON', 'OFF']:
        return jsonify({'status': 'error', 'message': 'Invalid command'}), 400
    if ser is None:
        return jsonify({'status': 'error', 'message': 'Serial not connected'}), 500
    try:
        ser.write((cmd + '\n').encode())
        data['system_state'] = (cmd == 'ON')

        twin_patch = {
            "properties": {
                "desired": {
                    "command": cmd
                }
            }
        }
        registry_manager.update_twin(DEVICE_ID, twin_patch, "*")

        return jsonify({'status': 'success'})
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

if __name__ == '__main__':
    threading.Thread(target=read_serial, daemon=True).start()
    app.run(host='0.0.0.0', port=5000)