#!/bin/bash
# gcolors.sh - A bash script that cycles through the 8 possible 
# colors for an RGB driven from GPIO pins. Each pin has 2 possible
# states (no PWM), ON and OFF, with 3 colors of LED, results in
# 2^3 possible colors. These colors are named as they are driven.
# LED used with this demo is Common Anode, so a 1 on the GPIO pin
# turns the LED off and a 0 turns it on. This inverse logic is
# reflected in the choice of variable substitutions.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
#
# Usage: 'colors2.sh <DELAY>"
#
UTYPE="<DELAY>"
. ./functions.sh

# Common Anode LEDs so ON is LOW, OFF is HIGH
ON=0
OFF=1

# Map the LED Colors to GPIO pins
RED=22
BLUE=23
GREEN=50

# check to see if we are running as sudo (root), if not, bail!
check_root

# Set the color ON time delay (in seconds)
DELAY=2

# If $1 is available, use it as the delay
if [ ! -z "$1" ]; then
    DELAY=$1
fi

function LED () {
  # LED $1 STATE $2
  #echo "LED (GPIO: $1) ($2)"
  ./gpio_write ${1} ${2}
}

function RED () {
  # LED $1 STATE $2
  LED ${RED} ${1}
}

function GRN () {
  # LED $1 STATE $2
  LED ${GREEN} ${1}
}

function BLU () {
  # LED $1 STATE $2
  LED ${BLUE} ${1}
}

while [ 1 ]; do
    COLORS="red green blue magenta cyan yellow white"
    for color in $COLORS
    do 
        ./color.sh $color
        msleep ${DELAY}
    done
done

