oci   https://github.com/DOCGroup/MPC/tree/master/docs <br>

build *.idl

```shlel
tao_idl *.idl  create  
	MessengerC.cpp
	MessengerC.h
	MessengerC.inl
	MessengerS.cpp
	MessengerS.h
```

```shell
opendds_idl i-Sa -St 
```

create <br>
	MessengerTypeSupport.idl<br>
	MessengerTypeSupportImpl.cpp<br>
	MessengerTypeSupportImpl.h<br>

在想要 build 的 Project 中新增 project_name.mpc 就會自動生成  GNUmakefile
在建制完 project_name.mpc 後執行
```shell
mwc.pl -type gnuace
```
就會自動生成  GNUmakefile

自行撰寫  
	Publish.cpp  
	Subscriber.cpp  
	rtps.ini  
	DataReaderListenerImpl.h（選用）  
	DataReaderListenerImpl.cpp（選用）  
```shell
./publisher -DCPSConfigFile rtps.ini
./subscriber -DCPSConfigFile rtps.ini
```

Qos的資料再這裏面  
/home/zack/github/OpenDDS/dds/DdsDcpsCore.idl

## staitc ini setting
### 注意!!Currently, static discovery can only be used for endpoints using the RTPS UDP transport
1.設定 common
```idl
[common]
DCPSGlobalTransportConfig=myconfig
DCPSDefaultDiscovery=dis
DCPSDebugLevel=0
```
2.設定 discovery transport 和 config
```idl
[config/myconfig]
transports=the_rtps_transport
[transport/the_rtps_transport]
transport_type=rtps_udp
TTL=3
[rtps_discovery/dis]
TTL=5
```

3. 設定 topic endpoint (reader)
``` idl
[topic/mytopic]
type_name=Messenger::Message
name=A
[endpoint/myreader]
type=reader
domain=34
participant=0123456789ab //length 16 hex
entity=aabbcc //length 6 hex
topic=mytopic
```
4.datareader qos 設定  
```idl
[datareaderqos/readerqos]
reliability.kind=RELIABLE
```



