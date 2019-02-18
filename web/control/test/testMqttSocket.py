#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

"""

"""

mqttModulePath ="../mqttModule/"
mqttPublishFile = "socket_2_publish.py"
import subprocess
def main():
    cmd = "python3 " + mqttModulePath+mqttPublishFile
    print(cmd)
    subprocess.run(cmd.split(" "))
    print ("subprocess stop")
if __name__=="__main__":
    main()
