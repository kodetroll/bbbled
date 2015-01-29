#!/bin/bash
# Common Anode LEDs so ON is LOW, OFF is HIGH
ON=0
OFF=1

# Map the LED Colors to GPIO pins
RED=22
BLUE=23
GREEN=50

function LED () {
  # LED $1 STATE $2
  echo "LED (GPIO: $1) ($2)"
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
RED ${ON}
sleep 2
RED ${OFF}

# GREEN
echo "GREEN"
GRN ${ON}
sleep 2
GRN ${OFF}

# BLUE
echo "BLUE"
BLU ${ON}
sleep 2
BLU ${OFF}

# MAGENTA (RED + BLU)
echo "MAGENTA"
BLU ${ON}
RED ${ON}
sleep 2
RED ${OFF}
BLU ${OFF}

# CYAN (GRN + BLU)
echo "CYAN"
BLU ${ON}
GRN ${ON}
sleep 2
GRN ${OFF}
BLU ${OFF}

# YELLOW (RED + GRN)
echo "YELLOW"
RED ${ON}
GRN ${ON}
sleep 2
GRN ${OFF}
RED ${OFF}

# WHITE (RED + GRN + BLU)
echo "WHITE"
RED ${ON}
GRN ${ON}
BLU ${ON}
sleep 2
GRN ${OFF}
RED ${OFF}
BLU ${OFF}

