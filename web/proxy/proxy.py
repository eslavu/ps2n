from flask import Flask, jsonify, request
import serial
import threading
import time

app = Flask(__name__)

SERIAL_PORT = '/dev/ttyACM0'  # Adjust for your system, e.g. COM3 on Windows
BAUD_RATE = 9600
ser = None

data = {
    'temperature': None,
    'humidity': None,
    'system_state': False
}

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
                    temp_part = parts[0].split(':')
                    hum_part = parts[1].split(':')
                    if temp_part[0] == 'temp' and hum_part[0] == 'hum':
                        data['temperature'] = float(temp_part[1])
                        data['humidity'] = float(hum_part[1])
        except Exception as e:
            print(f"Serial read error: {e}")
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
        return jsonify({'status': 'success'})
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

if __name__ == '__main__':
    threading.Thread(target=read_serial, daemon=True).start()
    app.run(host='0.0.0.0', port=5000)