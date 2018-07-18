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
send_port = 9807
bind_ip = "0.0.0.0"
def main():
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    send_socket.connect((bind_ip,send_port))
    while(1):
        d = raw_input("input")
        if d=="-1":
            send_socket.close()
            break
        send_socket.send(d)
        print send_socket.recv(4096)

if __name__ =="__main__":
    main()

