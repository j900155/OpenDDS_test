# Network_config.py
# Design By j13tw@yahoo.com.tw
# Only for Raspi network_configure

# include class to use
import Network_config 
NC = Network_config.Net_config()
NTP = Network_config.Ntp_config()
TC = Network_config.Time_config()
FS = Network_config.File_search()

# inner Ethernet card
NC.eth0_dhcp()
NC.eth0_static(static_ip, netmask, gateway)
NC.eth0_static('192.168.0.200', '255.255.255.0', '192.168.0.1')
NC.eth0_dns('8.8.8.8')
NC.eth0_dual_dns('8.8.8.8', '8.8.4.4')

# usb to RJ45 Adapter
NC.eth1_dhcp()
NC.eth1_static(static_ip, netmask, gateway)
NC.eth1_static('192.168.0.200', '255.255.255.0', '192.168.0.1')
NC.eth1_dns('8.8.8.8')
NC.eth1_dual_dns('8.8.8.8', '8.8.4.4')

# Restart usb to RJ45 Adapter
# 004 -> USB bus_id
os.sys("./Rest.py -d 0004")

# Get usb to RJ45 Adapter Vender_ID
os.sys('lsusb | grep "Realtek" | cut -c16,17,18')

# NTP Server time check 
NTP.ntp_set('TIME.google.com')

# date / time control for user By hands
TC.date_set('2018', '07', '31') 
TC.time_set('20', '10', '30')

# get on path " .ini " file list
FS.ini_list() 