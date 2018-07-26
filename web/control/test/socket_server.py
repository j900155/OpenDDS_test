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
send_port = 9808
recv_port = 9807
bind_ip = "0.0.0.0"
def main():
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #send_socket.bind((bind_ip,send_port))
    send_socket.bind((bind_ip,recv_port))
    send_port.listen(2)
    
    (clientsocket, address) = send_port.accept()


if __name__ =="__main__":
    print "ip {}  port {}".format(bind_ip, send_port)


