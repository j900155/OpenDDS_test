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
send_port = 9807
bind_ip = "0.0.0.0"
def main():
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    send_socket.connect((bind_ip,send_port))
    send_socket.send("recv")
    while(1):
        print send_socket.recv(4096)
        now_time = time.time()
        print(now_time - int(now_time))

if __name__ =="__main__":
    main()

