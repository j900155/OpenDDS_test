#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8



from subprocess import Popen, PIPE, STDOUT
#from multiprocessing import Process, Queue
import  threading
import time
#get_ini = "-DCPSConfigFIle rtps.ini"
#pub_cmd = "./publisher " + get_ini
#sub_cmd = "./subscriber " + get_ini
#set_time_pub = [20,50,100]
#set_time_sub = [1]
#pakage_size = [50,100,150,200,250]

class run_pub(threading.Thread):
    def __init__(self, pub_cmd,topic ="A",set_pub_time = 1000):
        super(run_pub, self).__init__()
        self.pub_cmd = pub_cmd
        self.set_pub_time = set_pub_time
        self.topic = topic
        print("publish init")
    def run(self):
        print ("dds publish start")
        print self.pub_cmd
        self.pub = Popen(self.pub_cmd.split(" "), stdin=PIPE,stdout=PIPE, stderr=STDOUT)
        print str(self.pub.pid)
        get_return = ""
        while(self.pub.poll() == None):
            get_return = (self.pub.stdout.readline())
            print("pub " + str(get_return))
            if(get_return == "topic name? \n"):
                self.pub.stdin.write(self.topic+"\n")
            elif(get_return == "delay us\n"):
                delay_time = str(int(self.set_pub_time* 1000)) + "\n"
                self.pub.stdin.write(delay_time)
            elif(get_return =="exit\n"):
                print("pub exit")
                self.pub.stdin.write("exit\n")
                print str(self.pub.wait())
                break
            else:
                print(get_return)
        return 0
class run_sub(threading.Thread):
    def __init__(self, sub_cmd,topic="A", set_sub_time = 10):
        threading.Thread.__init__(self)
        self.sub_cmd = sub_cmd
        self.topic = topic
        self.set_sub_time = set_sub_time

    def run(self):
        sub = Popen(self.sub_cmd.split(" "), stdin=PIPE,stdout=PIPE)
        get_return = ""
        while(sub.poll() == None):
            get_return = (sub.stdout.readline())
            print("sub " + str(get_return))
            if(get_return == "topic name?\n"):
                sub.stdin.write(self.topic+"\n")
            elif(get_return == "delay us\n"):
                delay_time = str(int(self.set_sub_time* 1000)) + "\n"
                sub.stdin.write(delay_time)
            elif(get_return == "exit\n"):
                break
            elif(get_return =="file name\n"):
                sub.stdout.write("run_test\n")
        return 0

