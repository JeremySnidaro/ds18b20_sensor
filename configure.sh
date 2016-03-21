#!/bin/sh

/usr/sbin/modeprobe w1-gpio
/usr/sbin/modeprobe w1-therm

# check if the two line needed in /boot/config.txt is present
# ....
# if the two line is not present write it at the end
echo \#1-wire setting \n dtoverlay=w1-gpio,gpiopin=4 > /boot/config.txt
# else do nothing reboot is not needed if the two line is already present

# Reboot is needed to apply the configuration
echo "Reboot is needed to apply the configuration"
#sudo reboot
