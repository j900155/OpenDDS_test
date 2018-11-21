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
bind_ip = "0.0.0.0"
def main(send_port):
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #send_socket.connect((bind_ip,send_port))
    count = 0
    data = {}
    data["from"]="A"
    while(1):
        data["msg"] = "test"+str(count)
        send_socket.send(str(data))
        r = send_socket.recv(2048)
        print (data)
        count +=1
        time.sleep(0.5)

if __name__ =="__main__":
    send_port = int(raw_input("port "))
    main(send_port)

