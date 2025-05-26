#!/bin/bash

export LOCAL_IP=$(python3 -c "import socket; s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM); s.connect(('8.8.8.8', 80)); print(s.getsockname()[0]); s.close()")

export IOTHUB_CONNECTION_STRING="HostName=ps2-web.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=szrWV8yEtZ34rjTX/I/ZQpiz6jWgtSbwUAIoTAxCsR8="
export DEVICE_ID="laptop"

export PS2_EMAIL_FROM="emilia.slavu@ligaac.ro"
export PS2_EMAIL_PASSWORD="jwiikkdfueezeris"
export PS2_EMAIL_TO="emilia.slavu@student.upt.ro"

if [ "$1" = "kill" ];
then
    pkill -f proxy.py
    pkill -f gunicorn

elif [ "$1" = "" ];
then
    cd iot-hub
    
    cd proxy
    python3 -m pip freeze > requirements.txt
    echo "Starting proxy.py..."
    python3 proxy.py &

    sleep 3

    cd ../app
    python3 -m pip freeze > requirements.txt
    echo "Starting gunicorn app..."
    gunicorn --reload --capture-output --log-level debug --bind 0.0.0.0:8000 app:app &

    cd ../..
    URL="http://$LOCAL_IP:8000"
    echo $URL
    xdg-open $URL
fi