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
create 
	MessengerTypeSupport.idl
	MessengerTypeSupportImpl.cpp
	MessengerTypeSupportImpl.h

在想要 build 的 Project 中新增 project_name.mpc 就會自動生成  GNUmakefile


自行撰寫
	Publish.cpp
	Subscriber.cpp
	DataReaderListenerImpl.h
	DataReaderListenerImpl.cpp

./subscriber -DCPSConfigFile rtps.ini


makefile
mwc.pl -type gnuace





