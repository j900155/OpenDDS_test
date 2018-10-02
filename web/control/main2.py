#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
from flask import Flask, render_template
from flask_socketio import SocketIO
import json
import socket
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

bindIP = "127.0.0.1"
pubPort = 9808
subPort = 9807
@socketio.on('publishSend')
def handle_test(data):
    print ("io test")
    print("get json {}".format(data))
    #jdata = json.loads(data)
    s = json.dumps(data)
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    send_socket.connect((bind_ip,pubPort))
    send_socket.send(s)
    r = send_socket.recv(1024)
    emit('publishReturn', {'data': r})
    send_socket.close()
@socketio.on('subscriberSend')
def handle_test(data):
    print ("io test")
    print("get json {}".format(data))
    #jdata = json.loads(data)
    s = json.dumps(data)
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    send_socket.connect((bind_ip,subPort))
    send_socket.send(s)
    r = send_socket.recv(1024)
    emit('subscriberReturn', {'data': r})
    send_socket.close()


@app.route("/testIO")
def test():
    return render_template('testIO.html')

if __name__ == '__main__':
    socketio.run(app)
