import requests
from flask import Flask, render_template, jsonify, request
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

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def get_data():
    try:
        resp = requests.get(f"{LOCAL_PROXY_URL}/data")
        resp.raise_for_status()
        return jsonify(resp.json())
    except Exception as e:
        return jsonify({'temperature': None, 'humidity': None, 'error': str(e)})

@app.route('/command', methods=['POST'])
def send_command():
    cmd = request.json.get('command')
    if cmd not in ['ON', 'OFF']:
        return jsonify({'status': 'error', 'message': 'Invalid command'}), 400
    try:
        resp = requests.post(f"{LOCAL_PROXY_URL}/command", json={'command': cmd})
        resp.raise_for_status()
        return jsonify(resp.json())
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500