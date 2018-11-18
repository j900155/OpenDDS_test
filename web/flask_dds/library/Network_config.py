import os, sys
import serial
import datetime, time
import subprocess

class Reboot_system():
    def __init__(self):
       self.command = "sudo init 6"

    def reboot(self):
       os.system(self.command)

class Watchdog_config():
    def __init__(self):
        self.cpu_short_load = "28"
        self.cpu_middle_load = "24"
        self.cpu_long_load = "12"
        self.cpu_temperature = "90"
        self.cpu_short_load_status = "Enable"
        self.cpu_middlet_load_status = "Enable"
        self.cpu_long_load_status = "Enable"
        f = open("/etc/modules", "r")
        for x in range(1,9):
            tmp = f.readline().split("\n\r")[0].split("\n")[0]
            if (tmp == "bcm2835_wdt"): break
            if (x == 8):
                os.system("sudo cp ./library/modules /etc/modules")
                os.system("sudo modprobe bcm2835_wdt")
                os.system("sudo apt-get install watchdog >/dev/null 2>&1")
                os.system("sudo cp ./library/watchdog.conf /etc/watchdog.conf")
                os.system("sudo service watchdog start")
                os.system("sudo update-rc.d watchdog defaults")

    def watchdog_status(self):
        file = open('/etc/watchdog.conf', 'r') 
        for x in range (1, 37):
            line = file.readline()
#            print(line)
            if (x == 10): 
                tmp = line.split(" ")
                if (len(tmp[0].split("#")) == 1): self.cpu_short_load_status = "Enable"
                else: self.cpu_short_load_status = "Disable"
                self.cpu_short_load = tmp[len(tmp)-1].split("\n")[0]
            if (x == 11): 
                tmp = line.split(" ")
                if (len(tmp[0].split("#")) == 1): self.cpu_middle_load_status = "Enable"
                else: self.cpu_middle_load_status = "Disable"
                self.cpu_middle_load = tmp[len(tmp)-1].split("\n")[0]
            if (x == 12): 
                tmp = line.split(" ")
                if (len(tmp[0].split("#")) == 1): self.cpu_long_load_status = "Enable"
                else: self.cpu_long_load_status = "Disable"
                self.cpu_long_load = tmp[len(tmp)-1].split("\n")[0]
            if (x == 36): 
                tmp = line.split(" ")
                self.cpu_temperature = tmp[len(tmp)-1].split("\n")[0]
#        print(self.cpu_short_load)
#        print(self.cpu_middle_load)
#        print(self.cpu_long_load)
#        print(self.cpu_temperature)
        return self.cpu_short_load_status, self.cpu_short_load, self.cpu_middle_load_status, self.cpu_middle_load, self.cpu_long_load_status, self.cpu_long_load, self.cpu_temperature

    def start_cpu_load_short(self):
        command = "sudo sed -i '10c max-load-1 = " + self_short_load + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def start_cpu_load_middle(self):
        command = "sudo sed -i '11c max-load-5 = " + self_middle_load + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def start_cpu_load_long(self):
        command = "sudo sed -i '12c max-load-15 = " + self_long_load + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"


    def set_cpu_load_short(self, percent):
        command = "sudo sed -i '10c max-load-1 = " + percent + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def set_cpu_load_middle(self, percent):
        command = "sudo sed -i '11c max-load-5 = " + percent + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def set_cpu_load_long(self, percent):
        command = "sudo sed -i '12c max-load-15 = " + percent + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def set_cpu_temperature(self, temperature):
        command = "sudo sed -i '36c max-temperature = " + temperature + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR" 

    def remove_cpu_load_short(self):
        command = "sudo sed -i '10c \#max-load-1 = " +  self.cpu_long_load  + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def remove_cpu_load_middle(self):
        command = "sudo sed -i '11c \#max-load-5 = " +  self.cpu_middle_load  + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

    def remove_cpu_load_long(self):
        command = "sudo sed -i '12c \#max-load-15 = " + self.cpu_long_load + "' /etc/watchdog.conf"
        status = os.system(command)
        if (status == 0): return "OK"
        else: return "ERROR"

class Gps_time():
    def __init__(self):
        self.set_date = ""
        self.set_time = ""

    def get_time(self):
        try:
            self.gps = serial.Serial('/dev/ttyUSB0', 4800, timeout=1)
        except:
            return "ERROR"    
        while(1):
            response = self.gps.readline().decode('ascii')
#            print(response)
            if (response.split(',')[0] == "$GPRMC"):
                if(response.split(',')[1] != ""):
                    now = datetime.datetime.strptime(response.split(',')[1].split('.')[0], '%I%M%S')
#                    print("Now", now.hour+ 8, now.minute, now.second)
                    self.set_time = str(now.hour + 8) + ":" + str(now.minute) + ":" + str(now.second)
                    print(self.set_time)
                else:
                    return "GPS Pending"
                date = datetime.datetime.strptime(response.split(',')[9], '%d%m%y')
#                print("DATE : ", date.year, date.month, date.day)
                self.set_date = str(date.year) + "-" + str(date.month) + "-" + str(date.day)
#                print(set_date)
            if (response.split(',')[0] == "$GPGGA"):
                if(response.split(',')[1] != ""):
                    now = datetime.datetime.strptime(response.split(',')[1].split('.')[0], '%I%M%S')
#                    print("Now", now.hour+ 8, now.minute, now.second)
                    self.set_time = str(now.hour + 8) + ":" + str(now.minute) + ":" + str(now.second)
                    print(self.set_time)
                else:
                    return "GPS Pending"
                now = datetime.datetime.strptime(response.split(',')[1].split('.')[0], '%I%M%S')
#                print("Now", now.hour+ 8, now.minute, now.second)
                self.set_time = str(now.hour + 8) + ":" + str(now.minute) + ":" + str(now.second)
#                print(set_time)
            if (self.set_time != "" and self.set_date != ""):
#               print("set GPS time")
                os.system("sudo timedatectl set-ntp 0")
                command = 'sudo date -s "' + self.set_date + ' ' + self.set_time + '"'
                os.system(command)
                break
        self.gps.close()
        return "OK"

class File_search():
    def __init__(self):
        if (os.path.isdir("/home/pi/ini")): pass
        else: os.mkdir("/home/pi/ini") 

    def ini_list(self):
        self.ini_table = os.listdir('/home/pi/ini/')
        return  self.ini_table

class Time_config():
    def __init__(self):
        pass

    def get_now(self):
        now = datetime.datetime.now()
        year = str(now.year)
        if (int(now.month) < 10): month = "0" + str(now.month)
        else: month = str(now.month)
        if (int(now.day) < 10): day = "0" + str(now.day)
        else: day = str(now.day)
        if (int(now.hour) < 10): hour = "0" + str(now.hour)
        else: hour = str(now.hour)
        if (int(now.minute) < 10): minute = "0" + str(now.minute)
        else: minute = str(now.minute)
        if (int(now.second) < 10): second = "0" + str(now.second)
        else: second = str(now.second)
        response = year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second
        return response
   
    def date_set(self, year, month, date):
        os.system("sudo timedatectl set-ntp 0")
        now = datetime.datetime.now()
        self.date_command = 'sudo date -s "' + year + '-' + month + '-' + date + " " + str(now.hour) + ':' + str(now.minute) + ':' + str(now.second) + '"'
#        print(self.date_command)
        os.system(self.date_command)
        return "OK"
    
    def time_set(self, hour, minute, second):
        os.system("sudo timedatectl set-ntp 0")
        now = datetime.datetime.now()
        self.time_command = 'sudo date -s "' + str(now.year) + '-' + str(now.month) + '-' + str(now.day) + " " + hour + ':' + minute + ':' + second + '"'
#        print(self.time_command)
        os.system(self.time_command)
        return "OK"

class Ntp_config():
    def __init__(self):
#       need install ntpdate By 'sudo apt-get install ntpdate'
        os.system('timedatectl set-timezone "Asia/Taipei"')
#        os.system('sudo /etc/init.d/ntp stop >/dev/null 2>&1')
        os.system('sudo apt-get install ntpdate -y')
        try:
            f = open('/etc/network/ntp.log', 'r')
            f.close()
        except:
            os.system('cp ./library/ntp.log /etc/network/ntp.log')

    def ntp_set(self, ntp_host):
        os.system("sudo timedatectl set-ntp 0")
        self.ntp_command = 'sudo ntpdate ' + ntp_host + ' >/dev/null 2>&1'
        self.f = open('/etc/network/ntp.log', 'w')
        self.f.write(ntp_host)
        self.f.close()
        connect = os.system(self.ntp_command)
        if (connect == 0):
            return "OK"
        else:
            return "ERROR"

class Net_config():
    def __init__(self):
        try:
            f = open('/etc/network/interfaces.bak')
            f.close()
        except:
            os.system('sudo cp ./library/interfaces.bak /etc/network/interfaces')
        try:
            f = open('/etc/network/Restusb.py')
            f.close()
        except:
            os.system('sudo cp ./library/Restusb.py /etc/network/Restusb.py')

    def eth0_status(self):
        command = 'ip address show dev eth0 | grep "eth0" | awk "END {print}"'
        result = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        error_code = 0
        try:
            eth0 = str(result.communicate()[0]).split("\\n")[0].split("b'    ")[1]
            eth0_ip = str(eth0.split(" ")[1].split('/')[0])
            eth0_netmask = int(eth0.split(" ")[1].split('/')[1])
        except:
            error_code = 1
            eth0_ip = "disconnect"
            eth0_netmask = 0

        if(eth0_netmask <= 8 and error_code == 0):
            eth0_nm_end = ".0.0.0"
            value = 128
            count = 0
            for x in range(0, eth0_netmask):
                count = count + value
                value = value / 2
            eth0_nm = str(int(count)) + eth0_nm_end
            
        elif(eth0_netmask <= 16 and eth0_netmask > 8 and error_code == 0):
            eth0_netmask = eth0_netmask - 8
            eth0_nm_head = "255."
            eth0_nm_end = ".0.0"
            value = 128
            count = 0
            for x in range(0, eth0_netmask):
                count = count + value
                value = value / 2
            eth0_nm = eth0_nm_head + str(int(count)) + eth0_nm_end

        elif(eth0_netmask <= 24 and eth0_netmask > 16 and error_code == 0):
            eth0_netmask = eth0_netmask - 16
            eth0_nm_head = "255.255."
            eth0_nm_end = ".0"
            value = 128
            count = 0
            for x in range(0, eth0_netmask):
                count = count + value
                value = value / 2
            eth0_nm = eth0_nm_head + str(int(count)) + eth0_nm_end

        elif(eth0_netmask <= 32 and eth0_netmask > 24 and error_code == 0):
            eth0_netmask = eth0_netmask - 24
            eth0_nm_head = "255.255.255."
            eth0_netmask = eth0_netmask
            value = 128
            count = 0
            for x in range(0, eth0_netmask):
                count = count + value
                value = value / 2
            eth0_nm = eth0_nm_head + str(int(count))
        else:
            eth0_nm = "disconnect"

        command = 'ip r show dev eth0 | grep default'
        result = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        try:
            eth0_gw = str(result.communicate()[0]).split(" ")[2]
        except:
            eth0_gw = "not use"

#        print(eth0)
        print("eth0")
        print("eth0_ip :", eth0_ip)
        print("eth0_nm :", eth0_nm)
        print("eth0_gw :", eth0_gw)
        return eth0_ip, eth0_nm, eth0_gw
    
    def eth1_status(self):
        command = 'ip address show dev eth1 | grep "eth1" | awk "END {print}"'
        result = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        error_code = 0
        try:
            eth1 = str(result.communicate()[0]).split("\\n")[0].split("b'    ")[1]
            eth1_ip = eth1.split(" ")[1].split('/')[0]
            eth1_netmask = int(eth1.split(" ")[1].split('/')[1])
        except:
            error_code = 1
            eth1_ip = "disconnect"
            eth1_netmask = 0

        if(eth1_netmask <= 8 and error_code == 0):
            eth1_nm_end = ".0.0.0"
            value = 128
            count = 0
            for x in range(0, eth1_netmask):
                count = count + value
                value = value / 2
            eth1_nm = str(int(count)) + eth1_nm_end
            
        elif(eth1_netmask <= 16 and eth1_netmask > 8 and error_code == 0):
            eth1_netmask = eth1_netmask - 8
            eth1_nm_head = "255."
            eth1_nm_end = ".0.0"
            value = 128
            count = 0
            for x in range(0, eth1_netmask):
                count = count + value
                value = value / 2
            eth1_nm = eth1_nm_head + str(int(count)) + eth1_nm_end

        elif(eth1_netmask <= 24 and eth1_netmask > 16 and error_code == 0):
            eth1_netmask = eth1_netmask - 16
            eth1_nm_head = "255.255."
            eth1_nm_end = ".0"
            value = 128
            count = 0
            for x in range(0, eth1_netmask):
                count = count + value
                value = value / 2
            eth1_nm = eth1_nm_head + str(int(count)) + eth1_nm_end

        elif(eth1_netmask <= 32 and eth1_netmask > 24 and error_code == 0):
            eth1_netmask = eth1_netmask - 24
            eth1_nm_head = "255.255.255."
            value = 128
            count = 0
            for x in range(0, eth1_netmask):
                count = count + value
                value = value / 2
            eth1_nm = eth1_nm_head + str(int(count))
        else:
            eth1_nm = "disconnect"

        command = 'ip r show dev eth1 | grep default'
        result = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        try:
            eth1_gw = str(result.communicate()[0]).split(" ")[2]
        except:
            eth1_gw = "not use"

#        print(eth1)
        print("eth1")
        print("eth1_ip :", eth1_ip)
        print("eth1_nm :", eth1_nm)
        print("eth1_gw :", eth1_gw)
        return eth1_ip, eth1_nm, eth1_gw

    def eth0_dhcp(self):
        os.system("sudo sed -i '3c iface eth0 inet dhcp' /etc/network/interfaces")
        os.system("sudo sed -i '4c \\ ' /etc/network/interfaces")
        os.system("sudo sed -i '5c \\ ' /etc/network/interfaces")
        os.system("sudo sed -i '6c \\ ' /etc/network/interfaces")
        os.system('sudo ifdown eth0')
        os.system('sudo ifup --ignore-errors eth0')
        os.system('sudo supervisorctl restart all')
        os.system('sudo cp /etc/network/interfaces ./library/interfaces.bak')

    def eth1_dhcp(self):
        os.system("sudo sed -i '12c iface eth1 inet dhcp' /etc/network/interfaces")
        os.system("sudo sed -i '13c \\ ' /etc/network/interfaces")
        os.system("sudo sed -i '14c \\ ' /etc/network/interfaces")
        os.system("sudo sed -i '15c \\ ' /etc/network/interfaces")
        os.system('sudo ifdown eth1')
        os.system('sudo ifup eth1')
#        os.system('lsusb | grep "Realtek" | cut -c16,17,18 >/tmp/usb.txt')
#        self.usb_id = open('/tmp/usb.txt')
#        self.usb_reset = 'sudo python /etc/network/Restusb.py -d ' + self.usb_id.read()
#        os.system(self.usb_reset)
        os.system('sudo supervisorctl restart all')
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')


    def eth0_static(self, ip, netmask, gateway):
        os.system("sudo sed -i '3c iface eth0 inet static' /etc/network/interfaces")
        command = "sudo sed -i '4c address " + ip + "' /etc/network/interfaces"
        os.system(command)
        command = "sudo sed -i '5c netmask " + netmask + "' /etc/network/interfaces"
        os.system(command)
        command = "sudo sed -i '6c gateway " + gateway + "' /etc/network/interfaces"
        os.system(command)
        os.system('sudo ifdown eth0')
        os.system('sudo ifup --ignore-errors eth0')
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')

    def eth1_static(self, ip, netmask, gateway):
        self.f = open('/etc/network/interfaces', 'r+')
        self.f.seek(190)
        self.f.write('allow-hotplug eth1\n\n')
        os.system("sudo sed -i '12c iface eth1 inet static' /etc/network/interfaces")
        command = "sudo sed -i '13c address " + ip + "' /etc/network/interfaces"
        os.system(command)
        command = "sudo sed -i '14c netmask " + netmask + "' /etc/network/interfaces"
        os.system(command)
        command = "sudo sed -i '15c gateway " + gateway + "' /etc/network/interfaces"
        os.system(command)
        os.system('lsusb | grep "Realtek" | cut -c16,17,18 >/tmp/usb.txt')
        self.usb_id = open('/tmp/usb.txt')
        self.usb_reset = 'sudo python /etc/network/Restusb.py -d ' + self.usb_id.read()
        os.system(self.usb_reset)
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')

    def eth0_dns(self, dns):
        command = "sudo sed -i '7c dns-nameserver " + dns + "' /etc/network/interfaces"
        os.system(command)
        os.system("sudo sed -i '8c \\ ' /etc/network/interfaces")
        os.system('sudo ifdown eth0')
        os.system('sudo ifup --ignore-errors eth0')
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')

    def eth1_dns(self, dns):
        command = "sudo sed -i '16c dns-nameserver " + dns + "' /etc/network/interfaces"
        os.system(command)
        os.system("sudo sed -i '17c \\ ' /etc/network/interfaces")
        os.system('lsusb | grep "Realtek" | cut -c16,17,18 >/tmp/usb.txt')
        self.usb_id = open('/tmp/usb.txt')
        self.usb_reset = 'sudo python /etc/network/Restusb.py -d ' + self.usb_id.read()
        os.system(self.usb_reset)
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')
    
    def eth0_dual_dns(self, dns, sub_dns):
        command = "sudo sed -i '7c dns-nameserver " + dns + "' /etc/network/interfaces"
        os.system(command)
        command = "sudo sed -i '8c dns-nameserver " + sub_dns + "' /etc/network/interfaces"
        os.system(command)
        os.system('sudo ifdown eth0')
        os.system('sudo ifup --ignore-errors eth0')
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')
    
    def eth1_dual_dns(self, dns, sub_dns):
        command = "sudo sed -i '16c dns-nameserver " + dns + "' /etc/network/interfaces"
        os.system(command)
        command = "sudo sed -i '17c dns-nameserver " + sub_dns + "' /etc/network/interfaces"
        os.system(command)
        os.system('lsusb | grep "Realtek" | cut -c16,17,18 >/tmp/usb.txt')
        self.usb_id = open('/tmp/usb.txt')
        self.usb_reset = 'sudo python /etc/network/Restusb.py -d ' + self.usb_id.read()
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')

    def eth0_auto_dns(self):
        command = "sudo sed -i '7c dns-nameserver 8.8.8.8' /etc/network/interfaces"
        os.system(command)
        os.system("sudo sed -i '8c \\ ' /etc/network/interfaces")
        os.system('sudo ifdown eth0')
        os.system('sudo ifup --ignore-errors eth0')
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')
    
    def eth1_auto_dns(self):
        command = "sudo sed -i '16c dns-nameserver 8.8.8.8' /etc/network/interfaces"
        os.system(command)
        os.system("sudo sed -i '17c \\ ' /etc/network/interfaces")
        os.system('lsusb | grep "Realtek" | cut -c16,17,18 >/tmp/usb.txt')
        self.usb_id = open('/tmp/usb.txt')
        self.usb_reset = 'sudo python /etc/network/Restusb.py -d ' + self.usb_id.read()
        os.system('sudo cp /etc/network/interfaces /etc/network/interfaces.bak')
