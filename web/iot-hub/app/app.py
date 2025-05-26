import requests
from flask import Flask, render_template, request
import socket
import os

LOCAL_IP = os.getenv('LOCAL_IP')

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