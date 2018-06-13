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
pub_cmd = "./publisher " + get_ini
sub_cmd = "./subscriber " + get_ini
set_time_pub = [20,50,100]
set_time_sub = [1]
pakage_size = [50,100,150,200,250]

def tpub():
    pub = Popen(pub_cmd.split(" "), stdin=PIPE,stdout=PIPE)
    get_return = ""
    while(1):
        get_return = (pub.stdout.readline())
        print("pub " + str(get_return))
        if(get_return == "topic name? \n"):
            pub.stdin.write("A\n")
        elif(get_return == "delay us\n"):
            delay_time = str(set_time_pub[0]* 1000) + "\n"
            pub.stdin.write(delay_time)
        elif(get_return == "send data"):
            pub.stdin.write("A\n")
        elif(get_return == "end\n"):
            break
        else:
            print(get_return)

def tsub():
    sub = Popen(sub_cmd.split(" "), stdin=PIPE,stdout=PIPE)
    get_return = ""
    while(1):
        get_return = (sub.stdout.readline())
        print("sub " + str(get_return))
        if(get_return == "topic name? \n"):
            sub.stdin.write("A\n")
        elif(get_return == "delay us\n"):
            delay_time = str(set_time_sub[0]* 1000) + "\n"
            sub.stdin.write(delay_time)
        elif(get_return == "end\n"):
            break
        elif(get_return =="file name\n"):
            sub.stdout.write("run_test\n")
            break
        else:
            print(get_return)


p = Process(target=tpub)
s = Process(target=tsub)
p.start()
s.start()
p.join()
s.join()
