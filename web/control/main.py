#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

"""

"""
import socket,sys
import run_dds
import threading
import time
import json
import types
HOST = "0.0.0.0"
pub_PORT = 9808
sub_PORT = 9807

pub_dds_connect = ""

sub_client_connect = []
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


def publish_socket(pub_connect, first_data):
    """
    publish_socket client
    create dds publish thread and send data to dds publish
    use json to 
        create dds publish {"active":"create","cmd":"./publisher -DCPSConfigFIle rtps.ini","topic":"A"}
        get dds publish thread status {"active":"status"}
        kill dds publish {"active":"exit"}
    """ 
    global pub_dds_connect
    pub_dds = ""
    data = first_data
    while(1):
        #data = pub_connect.recv(4096)
        print ("pub recv data {}".format(data))
        print type(pub_dds)
        if len(data) < 1:
            print (len(data))
            break
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
                    print type(pub_dds)
                else:
                    print("exist")
            elif jdata["active"] =="status":
                if type(pub_dds) == type("str"):
                    print "pub dds status {}".format("not create")
                else:
                    print "pub dds status {}".format(pub_dds.isAlive())
            elif jdata["active"] == "exit":
                if str(type(pub_dds)) == "<class 'run_dds.run_pub'>":
                    #pub_dds.send("exit")
                    pub_dds_connect.send("exit")
                    pub_dds ==""
                break
        elif str(type(pub_dds)) == "<class 'run_dds.run_pub'>":
            #TODO data paser
            #...
            print "pub send data"
            pub_dds_connect.send(data)
        data = pub_connect.recv(4096)
        #time.sleep(5)
    pub_connect.close()
    print ("publish_socket end")

def subscriber_dds(sub_connect):
    global sub_client_connect
    while(1):
        data = sub_connect.recv(4096)
        print "subscriber dds {}".format(data)
        if len(data) < 1:
            print (len(data))
            print "subscriber_dds break"
            break

        for sub_client in sub_client_connect:
            print sub_client
            sub_client.send(data)
        #TODO data paser
        #...


def subscriber_socket(sub_connect, first_data):
    """
    subscriber_socket client
    create dds subscriber thread and recriver from dds publisher
    use json to 
        create dds subscriber {"active":"create","cmd":"./subscriber -DCPSConfigFIle rtps.ini","topic":"A"}
        get dds subscriver thread status {"active":"status"}
        kill dds subscriber {"active":"exit"}
    """
    global sub_dds
    #global sub_client_connect
    #sub_connect.settimeout(0.0)
    #sub_client_connect.append(sub_connect)
    data = first_data
    while(1):
        #data = sub_connect.recv(4096)
        print("sub recv data {}".format(data))
        if len(data) < 1:
            print data
            sub_client_connect.remove(sub_connect)
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
                print ("sub type".format(type(sub_dds)))
                if str(type(sub_dds)) == "<class 'run_dds.run_sub'>":
                        print "sub dds status {}".format(sub_dds.isAlive())
                else:
                    print "sub dds status {}".format("not create")
            elif jdata["active"] == "exit":
                if str(type(pub_dds)) == "<class 'run_dds.run_sub'>":
                    sub_dds_connect.send("exit")
                    sub_dds_connect = ""
                break
        data = sub_connect.recv(4096)
 
def creat_subscriber_server():
    global sub_client_connect
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.err, msg:
        sys.stderr.write("ERROR {} ".format(msg))
        sys.exit(1)
    server.bind((HOST, sub_PORT))
    server.listen(10)
    print ("start subscriber server port {}".format(sub_PORT))
    while(1):
        conn, addr = server.accept()
        print ("connect {} addr {}".format(conn, addr))
        data = conn.recv(4096)
        print ("recv data {}".format(data))
        if data =="subscriber":
            sub_server = threading.Thread(target=subscriber_dds,args=[conn])
            sub_server.start()
        elif data =="recv":
            sub_client_connect.append(conn)
        else:
            sub_client = threading.Thread(target=subscriber_socket,args=[conn, data])
            sub_client.start()

def create_publish_server():
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.err, msg:
        sys.stderr.write("ERROR {} ".format(msg))
        sys.exit(1)
    server.bind((HOST, pub_PORT))
    server.listen(10)
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
            pub_client = threading.Thread(target=publish_socket,args=[conn, data])
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
