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
RED=23
BLUE=2
GREEN=50

# Set the color ON time delay (in seconds)
DELAY=2

# Set defined LED to specified duty cycle
function LED () {
	./setduty,sh ${1} ${2}
}

# Set RED LED PWM Duty Cycle
function Red () {
	# RED $1
	LED ${RED} ${1}
}

# Set GRN LED PWM Duty Cycle
function Grn () {
	# GRN $1
	LED ${GREEN} ${1}
}

# Set BLU LED PWM Duty Cycle
function Blu () {
	# BLU $1
	LED ${BLUE} ${1}
}

# Set RGB LED states
function set_color () {
	Red ${1}
	Grn ${2}
	Blu ${3}
}

# check to see if we are running as sudo (root), if not, bail!
check_root

./pwm_init ${RED}
./pwm_init ${GRN}
./pwm_init ${BLU}

Color_Red=$1
if [ -z "$Color_Red" ]; then
	echo "No RED value specified"
    usage
    exit(1)
fi

Color_Green=$1
if [ -z "$Color_Green" ]; then
	echo "No GREEN value specified"
    usage
    exit(1)
fi

Color_Blue=$1
if [ -z "$Color_Blue" ]; then
    echo "No BLUE value specified"
    usage
    exit(1)
fi

# Set RGB LED states
set_color ${Color_Red} ${Color_Green} ${Color_Blue}
