#!/bin/bash
# colors.sh - A bash script that cycles through the 8 possible 
# colors for an RGB driven from GPIO pins. Each pin has 2 possible
# states (no PWM), ON and OFF, with 3 colors of LED, results in
# 2^3 possible colors. These colors are named as they are driven.
# LED used with this demo is Common Anode, so a 1 on the GPIO pin
# turns the LED off and a 0 turns it on. This inverse logic is
# reflected in the choice of variable substitutions.

# Common Anode LEDs so ON is LOW, OFF is HIGH
ON=0
OFF=1

# Map the LED Colors to GPIO pins
RED=22
BLUE=23
GREEN=50

# Set the color ON time delay (in seconds)
DELAY=2

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

# RED
echo "RED"
./color.sh "red"
sleep ${DELAY}
./color.sh "black"

# GREEN
echo "GREEN"
./color.sh "green"
sleep ${DELAY}
./color.sh "black"

# BLUE
echo "BLUE"
./color.sh "blue"
sleep ${DELAY}
./color.sh "black"

# MAGENTA (RED + BLU)
echo "MAGENTA"
./color.sh "magenta"
sleep ${DELAY}
./color.sh "black"

# CYAN (GRN + BLU)
echo "CYAN"
./color.sh "cyan"
sleep 2
./color.sh "black"

# YELLOW (RED + GRN)
echo "YELLOW"
./color.sh "yellow"
sleep 2
./color.sh "black"

# WHITE (RED + GRN + BLU)
echo "WHITE"
./color.sh "white"
sleep 2
./color.sh "black"

