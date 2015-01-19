#!/bin/bash
# blink.sh - A script to blink an LED attached to the specified GPIO pin.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
# Use CTRL-C to stop the script. Use unxport.sh to unexport the pin.
# Note that this script sets the direction register of the pin to OUTPUT
# and then toggles the value between 0 & 1
UTYPE=1
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

# Sleep time (blink on/off time)
TIME=2

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

# Check to see if the GPIO pin is already exported
if ! check_exported $PIN ; then xport $PIN; fi

# set direction to OUT
setdir 44 out

echo "Use CTRL-C to stop the script. Use 'unxport.sh $PIN' to unexport the pin."

while [ true ]; do
    # set GPIO pin to high ('1') - ON
    digwr $PIN 1
    sleep $TIME

    # set GPIO pin to low ('0') - OFF
    digwr $PIN 0
    sleep $TIME
done

# Done
