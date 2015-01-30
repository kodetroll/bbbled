#!/bin/bash
# toggle.sh - A script to toggle an already exported GPIO pin once and quit.
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

# Flip the pin state
toggle $PIN

# Done
