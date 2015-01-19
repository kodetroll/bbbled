#!/bin/bash
# unxport.sh - A script to remove the specified GPIO pin from the export map.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
UTYPE=1
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

# Check to see if the GPIO pin is already exported, if so, then unexport it!
if check_exported $PIN ; then unxport $PIN; fi

# Done
