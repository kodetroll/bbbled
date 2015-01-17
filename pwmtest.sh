#!/bin/bash
# pwmtest.sh - A script to test PWM of an LED attached to the specified 
# GPIO pin.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
# Use CTRL-C to stop the script. Use unxport.sh to unexport the pin.

BASE="/sys/class/pwm"

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
PWMPIN="$BASE/ehrpwm.1"

cd /sys/class/pwm/ehrpwm.1\:0
cat request
echo 1 > request
echo 1 > run
echo 100 > period_freq
echo 10 > duty_percent

#when done:
echo 0 > request
