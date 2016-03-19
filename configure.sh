#!/bin/sh

sudo modeprobe w1-gpio
sudo modeprobe w1-therm

# check if the two line needed in /boot/config.txt is present
# ....

echo \#1-wire setting \n dtoverlay=w1-gpio,gpiopin=4 > /boot/config.txt

# Reboot is needed to apply the configuration
sudo reboot
