#!/bin/bash
# digitalread.sh - A script to read an already exported GPIO pin and print
# it's status to STDOUT.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html

GPIO="/sys/class/gpio"

function usage () {
    echo "Usage: $0 <GPIO#>"
}

# check to see if we are running as sudo (root), if not, bail!
if ! id | grep -q root; then
        echo "must be run as root"
        exit
fi

if [ -z "$1" ]; then
    echo "No GPIO pin specified, exiting!"
    usage
    exit 0
fi

PIN=$1
# define the GPIO PIN
GPIOPIN="$GPIO/gpio$PIN"

# set to high
echo high > $GPIOPIN/direction
echo high > $GPIOPIN/direction

# set to low
echo low > $GPIOPIN/direction