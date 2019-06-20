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

def Create(ip,send_port,cmd):
    send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    send_socket.connect((ip,send_port))
    send_socket.send(cmd)
    print (send_socket.recv(1024))
    send_socket.close()
def main():
    bind_ip = "0.0.0.0"
    pubCMD = '{"active":"create","cmd":"./publisher -DCPSConfigFile rtps.ini","topic":"A"}'
    subCMD = '{"active":"create","cmd":"./subscriber -DCPSConfigFile rtps.ini","topic":"A"}'
    Create(bind_ip,9808,pubCMD)
    Create(bind_ip,9807,subCMD)
if __name__ =="__main__":
    main()

