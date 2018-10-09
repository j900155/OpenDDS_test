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
bind_ip = "0.0.0.0"
def main(send_port):
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    send_socket.connect((bind_ip,send_port))
    while(1):
        d = raw_input("input")
        if d=="-1":
            send_socket.close()
            break
        else:
            send_socket.send(d)
            print (send_socket.recv(1024))

if __name__ =="__main__":
    send_port = int(raw_input("port "))
    main(send_port)

