#!/bin/bash
# rgbcolor.sh - A bash script that lights an RGB LED based on the 
# provided RGB colors using PWM.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
#
# Usage: 'color.sh <COLORNAME>'
#
UTYPE="<COLOR R> <COLOR G> <COLOR B>"
. ./functions.sh

# Common Anode LEDs so ON is LOW, OFF is HIGH
ON=0
OFF=1

# Map the LED Colors to GPIO pins
REDLED=23
BLULED=2
GRNLED=50

# Set the color ON time delay (in seconds)
DELAY=2

# Set defined LED to specified duty cycle
function LED () {
	local DC=100-${2}
	./setduty.sh ${1} ${DC}
}

# Set RED LED PWM Duty Cycle
function Red () {
	LED ${REDLED} ${1}
}

# Set GRN LED PWM Duty Cycle
function Grn () {
	LED ${GRNLED} ${1}
}

# Set BLU LED PWM Duty Cycle
function Blu () {
	LED ${BLULED} ${1}
}

# Set RGB LED states
function set_color () {
	Red ${1}
	Grn ${2}
	Blu ${3}
}

# check to see if we are running as sudo (root), if not, bail!
check_root

./pwm_init.sh ${REDLED}
Red 0
./pwm_init.sh ${GRNLED}
Grn 0
./pwm_init.sh ${BLULED}
Blu 0

Color_Red=$1
if [ -z "$Color_Red" ]; then
	echo "No RED value specified"
    usage
    exit 1
fi

Color_Green=$1
if [ -z "$Color_Green" ]; then
	echo "No GREEN value specified"
    usage
    exit 1
fi

Color_Blue=$1
if [ -z "$Color_Blue" ]; then
    echo "No BLUE value specified"
    usage
    exit 1
fi

# Set RGB LED states
set_color ${Color_Red} ${Color_Green} ${Color_Blue}
