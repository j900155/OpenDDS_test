#!/bin/bash

dhcp="/etc/dhcpcd.conf"
re_start="reboot"

#echo -n "Please input you static IP : "
#read IP

#echo -n "Please input you router : "
#read router

#echo -n "Please input you DNS : "
#read dns


setting=`cat dhcp.log > /etc/dhcpcd.conf
         echo "interface eth0" >> /etc/dhcpcd.conf
         echo "static ip_address="$1"" >> /etc/dhcpcd.conf
         echo "static routers="$2"" >> /etc/dhcpcd.conf
         echo "static domain_name_servers="$3"" >> /etc/dhcpcd.conf
        `
if [ -e $dhcp ]
then
    cat $dhcp >> a.log
    $setting
    if [ $? ]
    then
        echo 'Success ' ;sleep 1
    else
        echo 'Fail ' ;sleep 1
    fi
else
    $setting
    if [ $? ]
    then
        echo 'Success ' ;sleep 1
    else
        echo 'Fail ' ;sleep 1
    fi
fi

$re_start

