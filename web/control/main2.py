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
from flask_socketio import SocketIO,emit
import json
import socket
import time
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

bindIP = "127.0.0.1"
pubPort = 9808
subPort = 9807
@socketio.on('publishSend')
def handle_test(data):
    print ("publsihSend")
    print("get json {}".format(data))
    #jdata = json.loads(data)
    s = json.dumps(data)
    s = str.encode(s)
    print(s)
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    send_socket.connect((bindIP,pubPort))
    send_socket.send(s)
    r = send_socket.recv(1024)
    r = str(r,encoding="utf8")
    print ("pub r ",r)
    if len(r)>0:
        emit('publishReturn', {'data': r})
    send_socket.close()
@socketio.on('subscriberSend')
def handle_test(data):
    print ("subscriberSend")
    print("get json {}".format(data))
    #jdata = json.loads(data)
    s = json.dumps(data)
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    send_socket.connect((bindIP,subPort))
    print("50 " +s)
    s = str.encode(s)
    send_socket.send(s)
    r = send_socket.recv(1024)
    r = str(r,encoding="utf8")
    emit('subscriberReturn', {'data': r})
    send_socket.close()

@socketio.on('subscriberRecevieStart')
def subscriberRecv(data):
    print ("subscriberRecevieStart")
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    send_socket.connect((bindIP,subPort))
    send_socket.send(b"socketio")
    emit('subscriberRecevie', {'data': "start subscriber recevie"})
    send_socket.settimeout(3)
    r = ""
    #while(1):
    print ("67")
    #try:
    #    r = send_socket.recv(512)
    #    r = str(r,encoding="utf8")
    #    emit('subscriberRecevie', {'data': r})
    #except socket.timeout: 
    #    r = ""
    #if r =="exit" or r =="kill":
    #    #break
    #    pass
    send_socket.close()
@socketio.on("sub")
def socketSubSend(data):
    print("in sub {}".format(data))
    #emit("subscriberRecevie","12312")
    emit('subscriberRecevie', {'data': data})

@socketio.on('testRecvice2')
def sendWhile(data) :
    print ("testRecvice2")
    while(1):
        print ("testRecvice")
        emit("testRecvice","test")
        time.sleep(1)


@app.route("/testIO")
def test():
    return render_template('testIO.html')

if __name__ == '__main__':
    socketio.run(app,host = "0.0.0.0",port=9806)
