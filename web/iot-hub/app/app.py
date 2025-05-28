import requests
from flask import Flask, render_template, request, send_file
import os
import time

from dotenv import load_dotenv, find_dotenv
dotenv_path = find_dotenv()
load_dotenv(dotenv_path)

LOCAL_IP = os.getenv('LOCAL_IP')

EEPROM_LOG_FILE = os.getenv('EEPROM_LOG_FILE')

app = Flask(__name__)

LOCAL_PROXY_URL = f"http://{LOCAL_IP}:5000"

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        action = request.form.get('command')
        if action in ['ON', 'OFF']:
            try:
                requests.post(f"{LOCAL_PROXY_URL}/command", json={'command': action})
            except Exception as e:
                print(f"Error sending command: {e}")

    try:
        resp = requests.get(f"{LOCAL_PROXY_URL}/data")
        resp.raise_for_status()
        sensor_data = resp.json()
    except Exception as e:
        sensor_data = {'temperature': None, 'humidity': None, 'system_state': False, 'error': str(e)}

    return render_template('index.html', **sensor_data)

@app.route('/log')
def download_log():
    time.sleep(3)
    log_path = os.path.join(os.path.dirname(__file__), EEPROM_LOG_FILE)
    if os.path.exists(log_path):
        return send_file(log_path, as_attachment=False)
    else:
        return "Log file not found.", 404