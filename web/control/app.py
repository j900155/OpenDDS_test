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
from flask import Flask, request, render_template
from flask_socketio import SocketIO
import threading
import subprocess
from werkzeug.utils import secure_filename
app = Flask(__name__)
app.config['SECRET_KEY'] = 'password'
socketio = SocketIO(app)
filePath = "/home/zack/ini/"
@app.route("/")
def root():
    return render_template('index.html')
@app.route("/ping")
def ping():
    return render_template('/ping/index.html')
@app.route("/ping/getip", methods=['GET'])
def pingGetIp():
    ip = request.args.get('ip')
    cmd = "ping -c 1 " + str(ip)
    print cmd
    try:
               response = subprocess.check_output(cmd.split(" "), stderr=subprocess.STDOUT, \
                universal_newlines=True
                )
    except:
        response = "can not ip {}".format(ip)
    return response
@app.route("/dds/upload/ini", methods=['GET', 'POST'])
def DDSini():
    global filePath
    if request.method =='POST':
        if 'file' in request.files:
            f = request.files['file']
            if f != "":
                filename = secure_filename(f.filename)
                f.save(os.path.join(filePath)+filename)
    return render_template('/iniFile/index.html')
@app.route('/dds/show/ini')
def showIni():
    global filePath
    return str(os.listdir(filePath))
@app.route('/dds/start/publisher')
def startPublisher():
    pass
if __name__ == '__main__':
    app.run(debug=True)
#    socketio.run(app)
