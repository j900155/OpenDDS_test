#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
from subprocess import Popen, PIPE
from multiprocessing import Process
import time
get_ini = "-DCPSConfigFIle rtps.ini"
cmd = "../publisher " + get_ini
#set_time_pub = [20,50,100]
#pakage_size = [50,100,150,200,250]
set_time_pub = [20]
pakage_size = [50,100]

def tpub(cmd,delay_time,size):
    pub = Popen(cmd.split(" "), stdin=PIPE,stdout=PIPE)
    get_return = ""
    while(1):
        get_return = (pub.stdout.readline())
        print("pub " + str(get_return))
        if(get_return == "topic name? \n"):
            pub.stdin.write("A\n")
        elif(get_return == "delay us\n"):
            delay_time = str(int(delay_time)* 1000) + "\n"
            pub.stdin.write(delay_time)
            print "time {}".format(delay_time)
        elif(get_return == "send data\n"):
            pub.stdin.write(size+"\n")
            print "size {}".format(len(data))
        elif(get_return == "end\n"):
            break
        else:
            if len(get_return)>0:
                print(get_return)
            else:
                time.sleep(1)

for t in set_time_pub:
    for size in pakage_size:
        data = ""
        for k in range(0,size):
            data+="A"
        print len(data)
        p = Process(target=tpub, args=(cmd,t,data))
        p.start()
        p.join()
