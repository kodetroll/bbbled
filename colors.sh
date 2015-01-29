#!/bin/bash
ON=0
OFF=1
RED=22
BLUE=23
GREEN=50

function LED () {
  # LED $1 STATE $2
  echo "LED (GPIO: $1)"
  ./gpio_write ${1} ${2}
}

function RED () {
  # LED $1 STATE $2
  LED ${RED} ${1}
}

function BLU () {
  # LED $1 STATE $2
  LED ${BLUE} ${1}
}

function GRN () {
  # LED $1 STATE $2
  LED ${GREEN} ${1}
}

# RED
echo "RED"
RED ${ON}
sleep 2
RED ${OFF}

# BLUE
echo "BLUE"
BLU ${ON}
sleep 2
BLU ${OFF}

# GREEN
echo "GREEN"
GRN ${ON}
sleep 2
GRN ${OFF}

