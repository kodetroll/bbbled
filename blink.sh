#!/bin/bash
# blink.sh - A script to blink an LED attached to the specified GPIO pin.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
# Use CTRL-C to stop the script. Use unxport.sh to unexport the pin.
# Note that this script sets the direction register of the pin to OUTPUT
# and then toggles the value between 0 & 1
GPIO="/sys/class/gpio"

# Sleep time (blink on/off time)
TIME=2

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

# Check to see if the GPIO pin is already exported
if [ -d "$GPIOPIN" ]; then
    echo "GPIO Pin $PIN is already exported!"
else
    # if not, then we export the desired GPIO pin
    echo $PIN > $GPIO/export
    echo "GPIO Pin $PIN is now exported!"
    sleep 1
fi

# set direction to OUT
echo out > $GPIOPIN/direction

echo "Use CTRL-C to stop the script. Use unxport.sh to unexport the pin."

while [ true ]; do
    # set GPIO pin to high ('1') - ON
    echo 1 > $GPIOPIN/value
    sleep $TIME
    # set GPIO pin to low ('0') - OFF
    echo 0 > $GPIOPIN/value
    sleep $TIME
done
