#!/bin/bash
# digitalwrite.sh - A script to write to an already exported GPIO pin.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
UTYPE="<PIN#> <STATE>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

STATE=$2
# Check to see if a valid pin state argument has been supplied
check_statearg $PIN

# set to PIN to 'out'
setdir $PIN out

# set pin to specified value
digwr $PIN $STATE

# Done
