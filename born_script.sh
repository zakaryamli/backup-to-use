#!/bin/bash
# wall '#Architectur:' `uname -a`\
# '#CPU: ' `nproc --all`\
# '#vCPU: '`lscpu | grep 'Thread' | awk '{print $4}'`\
# '#Memory Usage: ' `free -m | grep Mem | awk '{printf "%d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100}'`\
# '#Disk Usage: ' `df -h --total | grep 'total' |awk '{printf "%.1f/%.1fGB (%s)", $3,$2,$5}'`\
# '#CPU load: ' `mpstat | grep all | awk '{printf("%.1f%%"), 100-$13}'`\
# '#Last boot: ' `who -b | awk '{print $3, $4}'`\
# '#LVM use: '`if [ $(lsblk | grep lvm | wc -l) != 0 ]; then echo yes; else echo no; fi;`\
# '#Connections TCP: '`netstat -an | grep ESTABLISHED | wc -l | tr -d '\n' && echo " ESTABLISHED"`\
# '#User log: '`users | wc -w`\
# '#Network: IP' `hostname -I`  "("`ip a | grep "link/ether" | awk '{print $2}'`")"\
# '#sudo: '``sudo cat /var/log/sudo/sudo.log | grep 'COMMAND' | wc -l` "cmd"`\
# wall '#Architecture:' "$(uname -a)" \
# '#CPU: ' "$(nproc --all)" \
# '#vCPU: ' "$(lscpu | grep 'Thread' | awk '{print $4}')" \
# '#Memory Usage: ' "$(free -m | grep Mem | awk '{printf "%d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100}')" \
# '#Disk Usage: ' "$(df -h --total | grep 'total' | awk '{printf "%.1f/%.1fGB (%s)", $3,$2,$5}')" \
# '#CPU load: ' "$(mpstat | grep all | awk '{printf("%.1f%%"), 100-$13}')" \
# '#Last boot: ' "$(who -b | awk '{print $3, $4}')" \
# '#LVM use: ' "$(if [ $(lsblk | grep lvm | wc -l) != 0 ]; then echo yes; else echo no; fi;)" \
# '#Connections TCP: ' "$(netstat -an | grep ESTABLISHED | wc -l | tr -d '\n' && echo " ESTABLISHED")" \
# '#User log: ' "$(users | wc -w)" \
# '#Network: IP' "$(hostname -I)"  "($(ip a | grep 'link/ether' | awk '{print $2}'))" \
# '#sudo: ' "$(sudo cat /var/log/sudo/sudo.log | grep 'COMMAND' | wc -l)" "cmd"
the_sleep_script
{
boot_min=$(uptime -s | cut -d':' -f2)
boot_sec=$(uptime -s | cut -d':' -f3)
sleep_time=$(( ($boot_min%10)*60 + $boot_sec ));

sleep $sleep_time
}
crontab 
*/10 * * * * /usr/local/bin/script.sh && /usr/local/bin/monitoring.sh
$(df -m --total | grep 'total' | awk '{printf "%d/%dGB (%s)", $3}')
$(df -h --total | grep 'total' | awk '{printf "%d/%dGB (%s)", $3,$2,$5}')
$(df -h --total | grep 'total' | awk '{printf "%d/%dGB (%s)", $3,$2,$5}')
df -m --total | grep total | awk '{printf("%d/%dGb (%d%%)"), $3, $2/1024, $5}'


echo -e "#Architecture:" "$(uname -a)\n"\
"#CPU physical:" "$(grep "physical id" /proc/cpuinfo | wc -l)\n"\
"#vCPU:" "$(cat /proc/cpuinfo | grep processor | wc -l)\n"\
"#Memory Usage:" "$(free --mega | grep Mem | awk '{printf "%d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100}')\n"\
"#Disk Usage:" "$(df -m --total | grep total | awk '{printf("%d/%dGb (%d%%)"), $3, $2/1024, $5}')\n"\
"#CPU load:" "$(mpstat | grep all | awk '{printf("%.1f%%"), 100-$13}')\n"\
"#Last boot:" "$(who -b | awk '{print $3, $4}')\n"\
"#LVM use:" "$(if [ $(lsblk | grep lvm | wc -l) != 0 ]; then echo yes; else echo no; fi;)\n"\
"#Connections TCP:" "$(netstat -an | grep ESTABLISHED | wc -l | tr -d '\n' && echo " ESTABLISHED")\n"\
"#User log:" "$(who | awk '{print$1}' | sort -u | wc -l)\n"\
"#Network: IP" "$(hostname -I)"  "($(ip a | grep 'link/ether' | awk '{print $2}'))\n"\
"#sudo:" "$(journalctl -q _COMM=sudo | grep "COMMAND" | wc -l)" "cmd" | wall









#!/bin/bash
boot_m=$(uptime -s | cut -d':' -f2)
boot_s=$(uptime -s | cut -d':' -f3)
sleep_time=$(( ($boot_m%10)*60 + $boot_s ));

sleep $sleep_time



#you'll need to install sysstat
#you'll need to install net-tools
#!/bin/bash
echo -e "#Architecture:" "$(uname -a)\n"\
"#CPU physical:" "$(grep "physical id" /proc/cpuinfo | wc -l)\n"\
"#vCPU:" "$(cat /proc/cpuinfo | grep processor | wc -l)\n"\
"#Memory Usage:" "$(free --mega | grep Mem | awk '{printf "%d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100}')\n"\
"#Disk Usage:" "$(df -m --total | grep total | awk '{printf("%d/%dGb (%d%%)"), $3, $2/1024, $5}')\n"\
"#CPU load:" "$(mpstat | grep all | awk '{printf("%.1f%%"), 100-$13}')\n"\
"#Last boot:" "$(who -b | awk '{print $3, $4}')\n"\
"#LVM use:" "$(if [ $(lsblk | grep lvm | wc -l) != 0 ]; then echo yes; else echo no; fi;)\n"\
"#Connections TCP:" "$(netstat -an | grep ESTABLISHED | wc -l | tr -d '\n' && echo " ESTABLISHED")\n"\
"#User log:" "$(who | awk '{print$1}' | sort -u | wc -l)\n"\
"#Network: IP" "$(hostname -I)"  "($(ip a | grep 'link/ether' | awk '{print $2}'))\n"\
"#sudo:" "$(journalctl -q _COMM=sudo | grep "COMMAND" | wc -l)" "cmd" | wall






Defaults        secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
Defaults        passwd_tries=3
Defaults        badpass_message="password is incorrect, try again"
Defaults        logfile="/var/log/sudo/sudo.log"
Defaults        log_input
Defaults        log_output
Defaults        requiretty
+212 6 21 42 06 23