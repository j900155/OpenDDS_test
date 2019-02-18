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
    print ("ip {}  port {}".format(bind_ip, port))
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #send_socket.bind((bind_ip,send_port))
    send_socket.bind((bind_ip,port))
    send_socket.listen(2)
    
    (clientsocket, address) = send_socket.accept()
    r = clientsocket.recv(64)
    print(r)
    data = {}
    data["broker"]=brokerIp
    data["topic"]=topic
    data["qos"]=MqttQos
    s = json.dumps(data)
    print(s)
    clientsocket.send(json.dumps(data).encode("utf-8"))
    r = clientsocket.recv(64)
    print(r)
    if r.decode("utf-8")=='{"status":"create"}':
        for x in range(0, 100):
            clientsocket.send(('{"send":"test data count ' + str(x) + '"}').encode())
            r = clientsocket.recv(2048)
            print('data_set_' + str(x) + ' --> return', r.decode('utf-8'))
    while(1):
        count = 0

if __name__ =="__main__":
    port = 9808
    main(9808)

