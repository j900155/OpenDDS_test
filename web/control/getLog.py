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
    #timeNow = "2018-10-11"
    secNow = 1542402369
    fileName =FilePath+"pub2018-11-16.txt"
    return get(secNow=secNow,fileName=fileName,choose="pub")
    #return get(choose="pub")
def get(timeNow=None,secNow=None,fileName=None,choose="pub"):
    global FilePath
    if timeNow==None and secNow==None:
        timeNow = time.strftime("%Y-%m-%d")
        secNow = int(time.time())+28800
        #print(secNow)
        #print(timeNow)
        fileName = FilePath+choose+str(timeNow)+".txt"
        print (fileName)

    #print(fileName)
    if os.path.isfile(fileName):
        with open(fileName) as f:
            allFile = f.readlines()
            checkTime = [0,0,0,0,0]
            showLog = [[0,0],[0,0],[0,0],[0,0],[0,0]]
            for i in range(0,5):
                checkTime[i]= secNow-60*i
                showLog[i][0] = secNow-60*i
            for rawFile in allFile:
                rawFile = rawFile.replace("\n","")
                sRawFile = rawFile.split(",")
                dataLen = len(str(sRawFile[2:-2]))
                dataTime = int(sRawFile[-1])
                print("dataTime {} dataLen {}".format(dataTime, dataLen))
                for i in range(0,4):
                    if dataTime < checkTime[i] and dataTime>= checkTime[i+1]:
                        print(dataLen)
                        showLog[i][1]+=dataLen
            #for i in range(0,5):
             #   showLog[i][0]=showLog[i][0]*1000
    else:
        return -1
    return showLog
if __name__ == "__main__":
    ans = main()
    print (ans)
