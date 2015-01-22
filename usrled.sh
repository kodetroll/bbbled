#!/bin/bash
# led.sh - Script to set state of user LED.
# usage: 'usrled.sh <LED> <STATE>' where LED is {0|3} and state is {0|1}
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries.
#
UTYPE=4
. ./functions.sh

check_root

check_ledarg $1

check_ledstatearg $2

LED="usr$1"
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
