#!/bin/bash
# color.sh - A bash script that lights an RGB LED based on the 
# provided color number

# Common Anode LEDs so ON is LOW, OFF is HIGH
ON=0
OFF=1

# Map the LED Colors to GPIO pins
RED=22
BLUE=23
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

function set_led_color () {
	echo "Color: $1"
  case "$1" in
  0) RED ${OFF}
     GRN ${OFF}
     BLU ${OFF}
     ;;
  1) RED ${ON}
     GRN ${OFF}
     BLU ${OFF}
     ;;
  2) RED ${OFF}
     GRN ${ON}
     BLU ${OFF}
     ;;
  3) RED ${OFF}
     GRN ${OFF}
     BLU ${ON}
     ;;
  4) RED ${ON}
     GRN ${ON}
     BLU ${OFF}
     ;;
  5) RED ${ON}
     GRN ${OFF}
     BLU ${ON}
     ;;
  6) RED ${OFF}
     GRN ${ON}
     BLU ${ON}
     ;;
  7) RED ${ON}
     GRN ${ON}
     BLU ${ON}
     ;;
  esac
}

function get_color_index () {
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
  "cyan") 
	RED ${ON}
	GRN ${OFF}
	BLU ${ON}
     ;;
  "magenta") 
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

# RED - 1
echo "RED"
get_color_index "red"
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

# GREEN - 2
echo "GREEN"
get_color_index "green"
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

# BLUE - 3
echo "BLUE"
get_color_index "blue"
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

# MAGENTA (RED + BLU)
echo "MAGENTA"
get_color_index "magenta"
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

# CYAN (GRN + BLU)
echo "CYAN"
get_color_index "cyan"
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

# YELLOW (RED + GRN)
echo "YELLOW"
get_color_index "yellow"
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

# WHITE (RED + GRN + BLU)
echo "WHITE"
get_color_index "white" 
#set_led_color $INDEX
sleep ${DELAY}
set_led_color 0

