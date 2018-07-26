#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 zack <zack@zack>
#
# Distributed under terms of the MIT license.

"""

"""
import subprocess
import time
pub =  subprocess.Popen(['./publisher', "-DCPSConfigFile rtps.ini"], stdout=subprocess.PIPE, stderr = subprocess.PIPE, stdin =subprocess.PIPE)
sub =  subprocess.Popen(['./subscriber', "-DCPSConfigFile rtps.ini"], stdout=subprocess.PIPE, stderr = subprocess.PIPE, stdin =subprocess.PIPE)
pub.stdin.write("A\n")
sub.stdin.write("A ")
time.sleep(1)
sub.stdout.read()
sub.stdout.flush()
"""
for i in ["rewrw ","0 ","rewrew ","1 ","5555 ","2 "]:
    print "pub " + i
    pub.stdin.write(i)
    time.sleep(0.5)
"""
pub.kill()
sub.kill()
