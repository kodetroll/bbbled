#!/bin/bash
# pinname.sh - A script to print the specified pin's sysfs device path
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
UTYPE="<GPIO#>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
#check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

# define the GPIO PIN
GPIOPIN="$GPIO/gpio$PIN"

# Show it
echo "$GPIOPIN"


