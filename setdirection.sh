#!/bin/bash
# setdirection.sh - A script to set the direction setting of the specified
# GPIO pin and print that value to STDOUT. If it is not exported, it will be
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
UTYPE=3
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

DIR=$2
# Check to see if a valid pin dir argument has been supplied
check_dirarg $DIR

# Check to see if the GPIO pin is already exported, if not, export it!
if ! check_exported $PIN ; then xport $PIN; fi

# print the value of direction register
setdir $PIN $DIR

# Done
