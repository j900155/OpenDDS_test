#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 zack <zack@zack>
#
# Distributed under terms of the MIT license.

import subprocess

pub= subprocess.Popen(['./publisher', '-DCPSConfigFile rtps2.ini'],stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.STDOUT, shell=True)
print pub.stdout.readline()

"""
pub= subprocess.Popen(['./publisher', '-DCPSConfigFile rtps.ini'],shell=False)
"""
