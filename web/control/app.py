#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
import os
from flask import Flask, request
from flask_socketio import SocketIO
import run_dds
import Queue
import threading
pub = ""
sub = ""
app = Flask(__name__)
app.config['SECRET_KEY'] = 'password'
socketio = SocketIO(app)
send_data = Queue.Queue()
@app.route('/send')
def send():
    return "<p>ok</p>"

@app.route('/start/publish')
def start_publish():
    global pub
    pub = run_dds.run_pub("./publisher -DCPSConfigFIle rtps.ini", send_data,1000)
    pub.start()
    send_data.put("A")
#    pub.join()
    return "<p>start publish</p>"

@app.route('/publish/send')
def publish_send():
    global send_data
    global pub
    data = request.args.get('data')
    send_data.put(data)
    pub.sendfunc()
    return "<p>publish send</p>"

@app.route('/publish/kill')
def publish_kill():
    r = pub.kill_publish()
    return "<p> kill" + str(r)  +"</p>"
@app.route('/start/subscriber')
def start_subscriber():
    sub = run_dds.run_sub("./subscriber -DCPSConfigFIle rtps.ini",1000)
    sub.start()
#    sub.join()
    return "<p> start subscriber</p>"

if __name__ == '__main__':
#    app.run(debug=True)
    socketio.run(app)
