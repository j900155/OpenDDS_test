#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
import glob
all_file = glob.glob('./*.txt')
print (all_file)
data = list()
for file_name in all_file:
    count = 0
    with  open(file_name) as f:
        for i in f:
            data.append(i)
            if count > 100:
                break
            count +=1
    for i in range(0,len(data)):
        #print (data[i])
        data[i] = data[i].replace('\n','')
        data[i] = data[i].split(',')
    #print (data)
    #print (line[0][3])
    all_time = 0
    #print (data[0])
    for i in data:
        all_time +=int(i[3])
    data = list()
    print (file_name + " "+ str(all_time/100) )
