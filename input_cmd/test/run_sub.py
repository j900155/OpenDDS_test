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
sub_cmd = "../subscriber " + get_ini
set_time_sub = [1]
pakage_size = [50,100,150,200,250]

names = ["5_20_1_50","5_20_1_100"]
def tsub(fileName, delay_time):
    sub = Popen(sub_cmd.split(" "), stdin=PIPE,stdout=PIPE)
    get_return = ""
    while(1):
        get_return = (sub.stdout.readline())
        print("sub " + str(get_return))
        if(get_return == "topic name?\n"):
            sub.stdin.write("A\n")
        elif(get_return == "delay us\n"):
            delay_time = str(delay_time* 1000) + "\n"
            sub.stdin.write(delay_time+"\n")
        elif(get_return == "exit\n"):
            break
        elif(get_return =="file name\n"):
            sub.stdin.write(fileName+"\n")
            print "file name {}".format(fileName)
        else:
            if len(get_return)>0:
                print(get_return)

for fileName in names:
    delay_time = 1
    s = Process(target=tsub, args=(fileName,delay_time))
    s.start()
    s.join()
