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
import json

send_port = 9808
recv_port = 9807
bind_ip = "0.0.0.0"

brokerIp = "127.0.0.1"
topic = "test"
MqttQos=0

def main(port=9808):
    print "ip {}  port {}".format(bind_ip, port)
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #send_socket.bind((bind_ip,send_port))
    send_socket.bind((bind_ip,port))
    send_socket.listen(2)
    
    (clientsocket, address) = send_socket.accept()
    r = clientsocket.recv(64)
    print(r)

if __name__ =="__main__":
    port = 9808
    main(9808)

