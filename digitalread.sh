#!/bin/bash
# digitalread.sh - A script to read the value of the specified GPIO pin and
# print it's value to STDOUT.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
UTYPE="<PIN#>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

# set to pin to 'input'
#setdir $PIN in

# read value and print it
if digrd $PIN; then echo "0"; else echo "1"; fi

# Done
