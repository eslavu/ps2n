import requests
from flask import Flask, render_template, request
import socket

def get_local_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

app = Flask(__name__)

LOCAL_PROXY_URL = f"http://{get_local_ip()}:5000"

@app.route('/', methods=['GET', 'POST'])
def index():
    # Handle ON/OFF button form
    if request.method == 'POST':
        action = request.form.get('command')
        if action in ['ON', 'OFF']:
            try:
                requests.post(f"{LOCAL_PROXY_URL}/command", json={'command': action})
            except Exception as e:
                print(f"Error sending command: {e}")

    # Always fetch fresh data from proxy
    try:
        resp = requests.get(f"{LOCAL_PROXY_URL}/data")
        resp.raise_for_status()
        sensor_data = resp.json()
    except Exception as e:
        sensor_data = {'temperature': None, 'humidity': None, 'system_state': False, 'error': str(e)}

    return render_template('index.html', **sensor_data)