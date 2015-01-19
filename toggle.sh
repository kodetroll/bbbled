#!/bin/bash
# toggle.sh - A script to toggle an already exported GPIO pin once and quit.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
UTYPE=1
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

toggle $PIN
#if digrd $PIN; then
#    # pin is currently 0, set to 1
#    digwr $PIN 1
#else
#    # pin is currently 1, set to 0
#    digwr $PIN 0
#fi

# Done
