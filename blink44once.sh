#!/bin/bash
# blink44once.sh - A script to blink an already export GPIO44 once and quit.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html

# set to high
echo high > /sys/class/gpio/gpio44/direction
# set to low
echo low > /sys/class/gpio/gpio44/direction
