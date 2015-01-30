#!/bin/bash
# strobe.sh - A script to strobe (toggle ON, then toggle OFF) an already
# exported GPIO pin once and quit.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
UTYPE="<PIN#>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

# Check to see if the GPIO pin is already exported
if ! check_exported $PIN ; then xport $PIN; fi

# set direction to OUT
setdir ${PIN} out

# Flip Pin State
./toggle.sh $PIN

# Flip Pin State
./toggle.sh $PIN

# Done
