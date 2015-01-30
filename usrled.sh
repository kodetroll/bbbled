#!/bin/bash
# led.sh - Script to set state of user LED.
# usage: 'usrled.sh <LED> <STATE>' where LED is {0|3} and state is {0|1}
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries.
#
UTYPE="<USRLED#> <STATE>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_ledarg $PIN

# Check to see if a valid led state argument has been supplied
check_ledstatearg $2

LED="usr$PIN"
STATE="none"
SYSFS="/sys/class/leds/beaglebone:green:${LED}/trigger"
if [ "$2" = "1" ]; then
    STATE="default-on"
fi

if [ -e "$SYSFS" ] ; then
    echo "Sending '$STATE' to '$SYSFS'"
    echo "$STATE" > ${SYSFS}
#/sys/class/leds/beaglebone\:green\:${LED}/trigger
fi

exit 0
