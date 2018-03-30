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




## static
Currently, static discovery can only be used for endpoints using the RTPS UDP transport  

