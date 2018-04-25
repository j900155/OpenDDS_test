#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
import socket,sys
import run_dds
import threading
import time
import json
HOST = "0.0.0.0"
pub_PORT = 9808
sub_PORT = 9807

pub_dds_connect = ""

sub_client_connect = ""
pub_dds = ""
sub_dds = ""

def heart_beat():
    pass
def publish_dds(pub_connect):
    print "publish dds"
    while(1):
        data = pub_connect.recv(4096)
        if data:
            print("publish_dds recv data {}".format(data))
    pub_connect.close()

"""
publish_socket client
create dds publish thread and send data to dds publish
use json to 
    create dds publish {"active":"create","cmd":"./publisher -DCPSConfigFIle rtps.ini","topic":"A"}
    get dds publish thread status {"active":"status"}
    kill dds publish {"active":"exit"}
    TODO kill function
"""
def publish_socket(pub_connect):
    global pub_dds_connect
    global pub_dds
    while(1):
        data = pub_connect.recv(4096)
        print ("recv data {}".format(data))
            
        if data.find("active") > -1:
            try:
                jdata = json.loads(data)
                print ("is json")
            except TypeError:
                pub_connect.send("json paser error") 
                continue
            print jdata["active"]
            if jdata["active"] =="create":
                print jdata["cmd"]
                print jdata["topic"]
                if type(pub_dds) == type("str"):
                    pub_dds = run_dds.run_pub(pub_cmd=jdata['cmd'],topic=jdata['topic'])
                    print ("pub dds start")
                    pub_dds.start()
                else:
                    print("exist")
            elif jdata["active"] =="status":
                if type(pub_dds) == type("str"):
                    print "pub dds status {}".format("not create")
                else:
                    print "pub dds status {}".format(pub_dds.isAlive())
            elif jdata["active"] == "exit":
                if type(pub_dds) != type("str"):
                    pub_dds_connect.send(data)
                break


        elif type(pub_dds) != type("str"):
            #TODO data paser
            #...
            pub_dds_connect.send(data)
        #time.sleep(5)
    pub_connect.close()
    print ("publish_socket end")

def subscriber_dds(sub_connect):
    global sub_client_connect
    data = sub_connect.recv(4096)
    #TODO data paser
    #...
    if(type(sub_client_connect) != type("str")):
        sub_client_connect.send(data)
"""
subscriber_socket client
create dds subscriber thread and recriver from dds publisher
use json to 
    create dds subscriber {"active":"create","cmd":"./subscriber -DCPSConfigFIle rtps.ini","topic":"A"}
    get dds subscriver thread status {"active":"status"}
    kill dds subscriber {"active":"exit"}
    TODO kill function
"""
def subscriber_socket(sub_connect):
    global sub_dds
    global sub_client_connect
    sub_client_connect = sub_connect

    while(1):
        data = sub_connect.recv(4096)
        print("sub recv data {}".format(data))
        if data == "exit":
            break
        if data.find("active") > -1:
            try:
                jdata = json.loads(data)
                print ("is json")
            except TypeError:
                print("json paser error") 
                continue
            print jdata["active"]
            if jdata["active"] =="create":
                print jdata["cmd"]
                print jdata["topic"]
                if type(sub_dds) == type("str"):
                    sub_dds = run_dds.run_sub(sub_cmd=jdata['cmd'],topic=jdata['topic'])
                    print ("sub dds start")
                    sub_dds.start()
                else:
                    print("exist")
            elif jdata["active"] =="status":
                if type(sub_dds) == type("str"):
                    print "sub dds status {}".format("not create")
                else:
                    print "sub dds status {}".format(sub_dds.isAlive())

def creat_subscriber_server():
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.err, msg:
        sys.stderr.write("ERROR {} ".format(msg))
        sys.exit(1)
    server.bind((HOST, sub_PORT))
    server.listen(2)
    print ("start publish server port {}".format(sub_PORT))
    while(1):
        conn, addr = server.accept()
        print ("connect {} addr {}".format(conn, addr))
        data = conn.recv(4096)
        print ("recv data {}".format(data))
        if data =="subscriber":
            sub_server = threading.Thread(target=subscriber_dds,args=[conn])
            sub_server.start()
        else:
            sub_client = threading.Thread(target=subscriber_socket,args=[conn])
            sub_client.start()

def create_publish_server():
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.err, msg:
        sys.stderr.write("ERROR {} ".format(msg))
        sys.exit(1)
    server.bind((HOST, pub_PORT))
    server.listen(2)
    print ("start publish server port {}".format(pub_PORT))
    while(1):
        conn, addr = server.accept()
        print ("connect {} addr {}".format(conn, addr))
        data = conn.recv(4096)
        print ("recv data {}".format(data))
        if data =="publisher":
            global pub_dds_connect
            pub_dds_connect = conn
            pub_server = threading.Thread(target=publish_dds,args=[conn])
            pub_server.start()
        else:
            pub_client = threading.Thread(target=publish_socket,args=[conn])
            pub_client.start()



if __name__ =="__main__":
    publish_server = threading.Thread(target=create_publish_server)
    subscriber_server = threading.Thread(target=creat_subscriber_server)
    time.sleep(1)
    
    print ("pub server start")
    publish_server.start()
    print ("sub server start")
    subscriber_server.start()

    publish_server.join()
    subscriber_server.join()
    print "end"
