#!/bin/bash
# fade.sh - A script that cycles the PWM duty cycle on the specified
# pwm pin up and down over the values stored in the UP and DN variables
# This script will run forever, until interrupted.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
UTYPE="<PIN#>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

# Sleep time (fade on/off time) in mS
DELAY=100

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

UP="10 20 30 40 50 60 70 80 90 100"
DN="90 80 70 60 50 40 30 20 10 1"

echo "Initializing PWM on ${PIN}"
./pwm_init.sh ${PIN}

echo "Press CTRL-C to stop"
while [ 1 ]; do
    for DC in $UP; do
        ./setduty.sh ${PIN} ${DC}
		msleep ${DELAY}
    done
    for DC in $DN; do
        ./setduty.sh ${PIN} ${DC}
		msleep ${DELAY}
    done
done
