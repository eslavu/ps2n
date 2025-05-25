from flask import Flask, render_template, jsonify, request
import threading
import serial
import time
import os

app = Flask(__name__)

SERIAL_PORT = '/dev/ACM0'
BAUD_RATE = 9600
ser = None

data = {
    'temperature': None,
    'humidity': None,
    'system_state': False
}

def get_serial():
    global ser
    if ser is None and os.path.exists(SERIAL_PORT):
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    return ser

def read_serial():
    global data, ser
    while True:
        try:
            ser = get_serial()
            if ser is None:
                continue
            
            line = ser.readline().decode('utf-8').strip()
            if line:
                # Expected format: temp:24.5,hum:60.2
                parts = line.split(',')
                temp_part = parts[0].split(':')
                hum_part = parts[1].split(':')
                if temp_part[0] == 'temp' and hum_part[0] == 'hum':
                    data['temperature'] = float(temp_part[1])
                    data['humidity'] = float(hum_part[1])
        except Exception as e:
            print(f"Error reading serial: {e}")
            ser = None
            time.sleep(1)
        time.sleep(0.1)

t = threading.Thread(target=read_serial, daemon=True)
t.start()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def get_data():
    return jsonify(data)

@app.route('/command', methods=['POST'])
def send_command():
    cmd = request.json.get('command')
    if cmd in ['ON', 'OFF']:
        try:
            ser.write((cmd + '\n').encode())
            data['system_state'] = (cmd == 'ON')
            return jsonify({'status': 'success'})
        except Exception as e:
            return jsonify({'status': 'error', 'message': str(e)}), 500
    return jsonify({'status': 'error', 'message': 'Invalid command'}), 400