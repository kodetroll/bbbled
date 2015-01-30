#!/bin/bash
# color.sh - A bash script that lights an RGB LED based on the 
# provided color name
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
#
# Usage: 'color.sh <COLORNAME>'
#
UTYPE="<COLOR NAME>"
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

# Map the RGB color to a name
black=0
red=1
green=2
blue=3
yellow=4
magenta=5
cyan=6
white=7

# Set defined LED to specified state
function LED () {
	# LED $1 STATE $2
	./gpio_write ${1} ${2}
}

# Set RED Led State 
function RED () {
	# RED $1
	LED ${RED} ${1}
}

function GRN () {
	# GRN $1
	LED ${GREEN} ${1}
}

function BLU () {
	# BLU $1
	LED ${BLUE} ${1}
}

function set_color () {
	echo "Color Name: $1"
	
	case "$1" in
		"black") 
			RED ${OFF}
			GRN ${OFF}
			BLU ${OFF}
		;;
		"red") 
			RED ${ON}
			GRN ${OFF}
			BLU ${OFF}
		;;
		"green") 
			RED ${OFF}
			GRN ${ON}
			BLU ${OFF}
		;;
		"blue") 
			RED ${OFF}
			GRN ${OFF}
			BLU ${ON}
		;;
		"yellow") 
			RED ${ON}
			GRN ${ON}
			BLU ${OFF}
		;;
		"magenta") 
			RED ${ON}
			GRN ${OFF}
			BLU ${ON}
		;;
		"cyan") 
			RED ${OFF}
			GRN ${ON}
			BLU ${ON}
		;;
		"white") 
			RED ${ON}
			GRN ${ON}
			BLU ${ON}
		;;
	esac
}

# check to see if we are running as sudo (root), if not, bail!
check_root

# Set RGB LED states by parsing color name
set_color $1
