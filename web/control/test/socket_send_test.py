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
bind_ip = "10.30.3.4"
def main(send_port):
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    send_socket.connect((bind_ip,send_port))
    count = 0
    data = {}
    data2 = {}
    data["send"]= ""
    data2["from"]="A"
    while(1):
        data2["message"] = "test"+str(time.ctime())
        j = json.dumps(data2)
        data["send"]=j
        j2 = json.dumps(data)
        print (j2)
        send_socket.send(j2)
        r = send_socket.recv(2048)
        print (r)
        count +=1
        time.sleep(0.01)

if __name__ =="__main__":
    send_port = int(raw_input("port "))
    main(send_port)

