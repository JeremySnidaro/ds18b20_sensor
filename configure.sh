#!/bin/sh
# lsmod to see the modeprobe currently in use
# modeinfo w1_gpio to have more information about it
echo w1-gpio >> /etc/modules 
echo w1-therm >> /etc/modules 

# check if the two line needed in /boot/config.txt is present
# ....
# if the two line is not present write it at the end
echo "#1-wire setting \ndtoverlay=w1-gpio,gpiopin=4" >> /boot/config.txt
#											not sure if gpiopin=4 is needed
# else do nothing reboot is not needed if the two line is already present

# Reboot is needed to apply the configuration
echo "Reboot is needed to apply the configuration"
sleep 5
reboot
