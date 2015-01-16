#!/bin/bash
# led.sh - Script to set state of user LED.
# usage: 'led.sh <LED> <STATE>' where LED is {0|3} and state is {0|1}
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries.
#

function usage () {
    echo "Usage: $0 <LED> <STATE>"
    echo "where:"
    echo "	LED is {0-3} for usr0 - usr3."
    echo "	STATE is {0|1} for OFF or ON"
    exit 0
}

if ! id | grep -q root; then
        echo "must be run as root"
        exit
fi

if [ -z "$1" ]; then
    echo "No LED specified, exiting!"
    usage
fi

if [ -z "$2" ]; then
    echo "No LED STATE specified, exiting!"
    usage
fi

LED="usr$1"
STATE="none"
if [ "$2" = "1" ]; then
    STATE="default-on"
fi
if [ -e /sys/class/leds/beaglebone\:green\:${LED}/trigger ] ; then
        echo "$STATE" > /sys/class/leds/beaglebone\:green\:${LED}/trigger
fi

exit 0
