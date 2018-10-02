#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

"""

"""
from subprocess import Popen, PIPE, STDOUT
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
pubStatus=0
sub_dds = ""
pub = ""
sub = ""
def heart_beat():
    pass
def publish_dds(pub_connect):
    print ("publish dds")
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
        create dds publish {"active":"create","cmd":"./publisher -DCPSConfigFile rtps.ini","topic":"A"}
        get dds publish thread status {"active":"status"}
        exit dds publish {"active":"exit"}
        kill dds publish {"active":"kill"}
        dds publish send data {"send":"your data"}
    """ 
    global pub_dds_connect
    global pub_dds
    global pubStatus
    data = ""
    jdata = ""
    pub_connect.settimeout(3)
    while(1):
        try:
            if first_data == "":
                data = pub_connect.recv(4096)
            else:
                data = first_data
                first_data = ""
            print ("pub recv data {}".format(data))
            print (type(pub_dds))
            if len(data) < 1:
                print (len(data))
                break
            try:
                s = str(data,encoding="utf8")
                jdata = json.loads(s)
                #print (jdata)
                print ("is json")
            except ValueError:
                pub_connect.send(b'json paser error')
                jdata = ""
            #print (type(jdata))
            if type(jdata) != dict:
                print ("not dict")
                pub_connect.send(b'json paser error')
                jdata = ""
            if "active" in jdata:
                print (jdata["active"])
                if jdata["active"] =="create":
                    print (jdata["cmd"])
                    print (jdata["topic"])
                    if type(pub_dds) == type("str"):
                        print ("pub dds type str")
                        pubStatus = 0
                    else:
                        if pub_dds.poll() ==None:
                            status = 1
                        else:
                            print ("poll not None")
                            pubStatus = 0

                    if pubStatus == 0:
                        print ("pub dds start")
                        tempSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                        tempSocket.connect((HOST,pub_PORT))
                        #s = "{'send':'"+jdata["topic"] + "'}"
                        tempSocket.send(b"create")
                        time.sleep(1)
                        tempSocket.send(str.encode(jdata["cmd"]))
                        time.sleep(1)
                        pub_dds_connect.send(str.encode(jdata["topic"]))
                        tempSocket.close()
                        print (type(pub_dds))
                        pub_connect.send(b'create')
                        pubStatus = 1
                    else:
                        print("exist")
                        pub_connect.send(b'exist')

                elif jdata["active"] =="status":
                    if pubStatus ==1:
                        #alive
                        pub_dds_connect.send(b"1")
                    else:
                        pub_dds_connect.send(b"0")

                elif jdata["active"] == "exit":
                    if str(type(pub_dds)) == "<class 'subprocess.Popen'>":
                        #pub_dds.send("exit")
                        pub_dds_connect.send(b'exit')
                        pub_dds =""
                        pubStatus = 0
                    break
                elif jdata["active"] == "kill":
                    pub_dds.kill()
                    pub_dds =""
                    pubStatus = 0
                    break
            elif "send" in jdata:
                if str(type(pub_dds)) == "<class 'subprocess.Popen'>":
                    print ("pub send data")
                    print ("pub_dds_connect type {}".format(type(pub_dds_connect)))
                    pub_dds_connect.send(str.encode(jdata["send"]))
                    pub_connect.send(str.encode(jdata["send"]))
                else:
                    pub_connect.send(b"not create")

        except socket.timeout:
            print ("timeout")
                #time.sleep(5)

    #pub_connect.close()
    print ("publish_socket end")

def subscriber_dds(sub_connect):
    global sub_client_connect
    while(1):
        data = sub_connect.recv(4096)
        print ("subscriber dds {}".format(data))
        if len(data) < 1:
            print (len(data))
            print ("subscriber_dds break")
            break

        for sub_client in sub_client_connect:
            print (sub_client)
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
            print (data)
            sub_client_connect.remove(sub_connect)
            break
        try:
            s = str(data,encoding="utf8")
            jdata = json.loads(s)
            print (jdata)
            print ("is json")
        except ValueError:
            sub_connect.send(b'json paser error')
            jdata = ""
        print (type(jdata))

        if "active" in jdata:
            print (jdata["active"])
            if jdata["active"] =="create":
                print (jdata["cmd"])
                print (jdata["topic"])
                if type(sub_dds) == type("str"):
                    sub_dds = run_dds.run_sub(sub_cmd=jdata['cmd'],topic=jdata['topic'])
                    print ("sub dds start")

                    sub_connect.send("create")
                    sub_dds.start()
                else:
                    print("exist")
                    sub_connect.send("exist")
            elif jdata["active"] =="status":
                print ("sub type".format(type(sub_dds)))
                if str(type(sub_dds)) == "<class 'run_dds.run_sub'>":
                        print ("sub dds status {}".format(sub_dds.isAlive()))
                        if(sub_dds.isAlive()):
                            sub_connect.send("True")
                        else:
                            sub_connect.send("Flase")
                else:
                    print ("sub dds status {}".format("not create"))
                    sub_connect.send("Flase")
            elif jdata["active"] == "exit":
                if str(type(pub_dds)) == "<class 'run_dds.run_sub'>":
                    sub_dds_connect.send("exit")
                    sub_dds_connect = ""
                break
        data = sub_connect.recv(4096)
 
def creat_subscriber_server():
    global sub_client_connect
    try:
        #server = socket.MSG_DONTROUTEcket(socket.AF_INET, socket.SOCK_STREAM)
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.err:
        msg = socket.err
        sys.stderr.write("ERROR sub {} ".format(msg))
        sys.exit(1)
    server.bind((HOST, sub_PORT))
    server.listen(10)
    print ("start subscriber server port {}".format(sub_PORT))
    while(1):
        conn, addr = server.accept()
        print ("connect {} addr {}".format(conn, addr))
        data = conn.recv(4096)
        print ("recv data {}".format(data))
        s = str(data, encoding="utf8")
        if s =="subscriber":
            sub_server = threading.Thread(target=subscriber_dds,args=[conn])
            sub_server.start()
        elif data =="recv":
            print (type(conn))
            sub_client_connect.append(conn)
        else:
            sub_client = threading.Thread(target=subscriber_socket,args=[conn, data])
            sub_client.start()

def create_publish_server():
    global pub_dds
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.err:
        msg = socket.err
        sys.stderr.write("ERROR pub {} ".format(msg))
        sys.exit(1)
    server.bind((HOST, pub_PORT))
    server.listen(10)
    print ("start publish server port {}".format(pub_PORT))
    while(1):
        conn, addr = server.accept()
        print ("connect {} addr {}".format(conn, addr))
        data = conn.recv(4096)
        print ("recv data {}".format(data))
        s = str(data, encoding="utf8")
        if s =="publisher":
            print("publisher")
            global pub_dds_connect
            pub_dds_connect = conn
            print(type(pub_dds_connect))
            pub_server = threading.Thread(target=publish_dds,args=[conn])
            pub_server.start()
        elif s=="create":
            print ("271")
            data = conn.recv(4096)
            s = str(data, encoding="utf8")
            print ("273" + s)
            pub_dds = Popen(s.split(" "))
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
    print ("end")
