import subprocess

cmd_pub = ['./publisher' ,'-DCPSConfigFile rtps.ini']
cmd_sub = ['./subscriber' ,'-DCPSConfigFile rtps.ini']

pub = subprocess.Popen(cmd_pub, stdout=subprocess.PIPE)
sub = subprocess.Popen(cmd_sub, stdout=subprocess.PIPE)

#pub_out, err = pub.communicate()
#print("pub")
#print(pub_out)

sub_out, err = sub.communicate()
print("sub")
print(sub_out)
array_sub = sub_out.split("\n")

for i in array_sub:
    print i

with open("time_log.text", "a+") as text:
    for i in array_sub:
        text.write(i + "\n")
