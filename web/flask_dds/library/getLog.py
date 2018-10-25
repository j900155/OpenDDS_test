
#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

"""
"""
import time
import os.path

"""
return list
"""
FilePath = "/home/pi/OpenDDS_test/web/control/log/"


def main():
    timeNow = "2018-10-11"
    secNow = 1539235432
    fileName = "/test/2018-10-11.txt"
    return get(timeNow, secNow, fileName, choose="")


def get(timeNow=None, secNow=None, fileName=None, choose="pub"):
    global FilePath
    if timeNow == None or secNow == None:
        timeNow = time.strftime("%Y-%m-%d")
        secNow = int(time.time())
        # print(secNow)
        # print(timeNow)
        fileName = FilePath+choose+str(timeNow)+".txt"
    showLog = []
    count = 0
    # print(fileName)
    if os.path.isfile(fileName):
        with open(fileName) as f:
            allFile = f.readlines()
            for rawFile in allFile:
                rawFile = rawFile.replace("\n", "")
                sRawFile = rawFile.split(",")
                if int(sRawFile[-1]) > (secNow+count*60):
                    dataLen = len(sRawFile[2:-2])
                    dataLen = len(str(sRawFile[2:-2]))
                    # print(sRawFile[-1])
                    if int(sRawFile[-1]) > (secNow+(count+1)*60) and count < 5:
                        s = int(time.time()*1000)+count*60*1000
                        showLog.append([s, dataLen])
                        # print(s)
                        count += 1
                        # print(count)
                    else:
                        break
    else:
        return -1
    return showLog


if __name__ == "__main__":
    ans = main()
    print(ans)
