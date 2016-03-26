#!/bin/sh

# lsmod to see the modeprobe currently in use
# modinfo w1_gpio to have more information about it, in raspberry a simple user can use
# this command but in debian you need to be root for modinfo

# Care if you use Red Hat/Fedora core/Cent OS 
# the file need to be /etc/modules.conf
echo w1-gpio >> /etc/modules 
echo w1-therm >> /etc/modules 

# check if the two line needed in /boot/config.txt is present
if ! grep -q 'dtoverlay=w1-gpio' /boot/config.txt ;
then
	# if the line is not present write it at the end
	echo "#1-wire setting \ndtoverlay=w1-gpio,gpiopin=4" >> /boot/config.txt
	#											not sure if gpiopin=4 is needed
	echo "Reboot is needed to apply the configuration"
	sleep 5
	reboot
fi

