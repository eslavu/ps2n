#!/bin/bash

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