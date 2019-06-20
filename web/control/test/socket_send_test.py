#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
import socket
import time
import json
bind_ip = "10.0.0.200"
def main(size):
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    send_socket.connect((bind_ip,9808))
    count = 0
    data = {}
    data2 = {}
    data["send"]= ""
    timeTmp = time.time()
    nowTime = 0
    d = ""
    for i in range(0,int(size)):
        d+="A"
    data["send"] = d
    while((nowTime - timeTmp)<10):
        nowTime = time.time()
        j2 = json.dumps(data)
        print (j2)
        print(nowTime-int(nowTime))
        send_socket.send(j2)
        r = send_socket.recv(2048)
        print (r)
        count +=1
        time.sleep(0.001)

if __name__ =="__main__":
    size = int(raw_input("size "))
    main(size)

