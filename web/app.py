from flask import Flask, render_template

app = Flask(__name__)

last_command = ""

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/command', methods=['GET'])
def get_command():
    return {'command': last_command}


@app.route('/send_command', methods=['POST'])
def send_command():
    global last_command
    last_command = "OFF" if last_command == "ON" else "ON"
    return redirect(url_for('index'))