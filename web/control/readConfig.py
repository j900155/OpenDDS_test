#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""
read config File to start dds
"""
import socket
from os.path import isfile
import json
hostIP="0.0.0.0"
filePath="/home/pi/OpenDDS_test/web/flask_dds/db/"
IniFilePath="/home/pi/ini/"

def readConfig(port=0,fileName=""):
    readFile =filePath+fileName
    print (readFile)
    if isfile(readFile):
        with open(readFile) as f:
            s = f.readline()
            s = s.replace("\n","")
            print (s)
            jdata = json.loads(s)
            try:
                print(jdata["type"])
                print(jdata["topic"])
                print(jdata["rtps"])
            except keyError:
                return -2
            jdata["rtps"]=IniFilePath+jdata["rtps"]
            sendSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sendSocket.connect((hostIP,port))
            data = {}
            data["active"] = "create"
            if jdata["type"] == "pub":
                data["cmd"] = "./publisher -DCPSConfigFile "+jdata["rtps"]
            elif jdata["type"] == "sub":
                data["cmd"] = "./subscriber -DCPSConfigFile "+jdata["rtps"]

            data["topic"]=jdata["topic"]
            cmd = json.dumps(data)
            b = str.encode(cmd)
            sendSocket.send(b)
            r = sendSocket.recv(1024)
            print(r)
            return 0
    else:
        return -1
if __name__ =="__main__":
    print("test")
    r = readConfig(port=9808,fileName="pub.json")
    print (r)

