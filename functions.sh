# functions.sh - Function include file for use with BBB LED Tool suite
#
# Usage: '. functions.sh'
#
# (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Board: Beagle Bone Black
#
# Some functions have code based on examples from:
# http://www.circuidipity.com/bbb-led.html

GPIO="/sys/class/gpio"

# define is_file_exists function
# $f -> store argument passed to the script
function file_exists () {
    local f="$1"
    [[ -f "$f" ]] && return 0 || return 1
}

# Basic usage format
function usage () {
    local N="$1"
    if [ -z "$N" ]; then N=1;fi
    if [ $N -eq 1 ]; then usage1; fi
    if [ $N -eq 2 ]; then usage2; fi
    if [ $N -eq 3 ]; then usage3; fi
}

function usage1 () {
    echo "Usage: $0 <GPIO#>"
}

function usage2 () {
    echo "Usage: $0 <GPIO#> <STATE>"
}

function usage3 () {
    echo "Usage: $0 <GPIO#> <DIR>"
}

# Check to see if the GPIO pin is already exported
function check_exported() {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi

    # define the GPIO PIN
    local GPIOPIN="$GPIO/gpio$PIN"

    if [ -d "$GPIOPIN" ]; then
#        echo "GPIO Pin $PIN is already exported!"
        return 0
    else
#        echo "GPIO Pin $PIN is NOT exported!"
        return 1
    fi
}

function xport () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi

#    echo "Pin: $PIN"
#    echo "GPIO: $GPIO"

    # export the desired GPIO pin
    echo $PIN > $GPIO/export

#    echo "GPIO Pin $PIN is now exported! ($GPIO)"
    sleep 1
}

function unxport () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi

#    echo "Pin: $PIN"
#    echo "GPIO: $GPIO"

    # export the desired GPIO pin
    echo $PIN > $GPIO/unexport
#    echo "GPIO Pin $PIN is now unexported! ($GPIO)"
}
# returns 0 for in, 1 for out
function getdir () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi

    # define the GPIO PIN
    local GPIOPIN="$GPIO/gpio$PIN"

    # Check to see if the GPIO pin is already exported, if not, export it!
    if ! check_exported $PIN ; then xport $PIN; fi

    # get the value of direction register
    local s=`cat $GPIOPIN/direction`

    # return a 1 for out, 0 for everything else
    [[ "$s" = "out" ]] && return 1 || return 0
}

function setdir () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi
    local DIR=$2
    if [ -z "$DIR" ]; then echo "No DIR Specified!"; exit 1; fi

    # define the GPIO PIN
    local GPIOPIN="$GPIO/gpio$PIN"

    # Check to see if the GPIO pin is already exported, if not, export it!
    if ! check_exported $PIN ; then xport $PIN; fi

    # print the value of direction register
    echo $DIR > $GPIOPIN/direction
}

function digrd () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi

    # define the GPIO PIN
    local GPIOPIN="$GPIO/gpio$PIN"

    # Check to see if the GPIO pin is already exported, if not, export it!
    if ! check_exported $PIN ; then xport $PIN; fi

    # NOTE: We dont set the direction to INPUT, we just read the state

    # get the state of 'value' register
    local s=`cat $GPIOPIN/value`

    # return a 1 for '1', 0 for everything else
    [[ "$s" = "1" ]] && return 1 || return 0

    # get GPIO pin state 0/1
#    cat $GPIOPIN/value
}

function digwr () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi
    local STATE=$2
    if [ -z "$STATE" ]; then echo "No STATE Specified!"; exit 1; fi

    # define the GPIO PIN
    local GPIOPIN="$GPIO/gpio$PIN"

    # Check to see if the GPIO pin is already exported, if not, export it!
    if ! check_exported $PIN ; then xport $PIN; fi

    # set GPIO PIN to out
    setdir $PIN out

    # set GPIO pin to specified state 0/1
    echo ${STATE} > $GPIOPIN/value
}

# toggle setting, if 0 then 1, if 1 then 0
function toggle () {
    local PIN=$1
    if [ -z "$PIN" ]; then echo "No PIN# Specified!"; exit 1; fi

    if digrd $PIN; then
        # pin is currently 0, set to 1
        digwr $PIN 1
    else
        # pin is currently 1, set to 0
        digwr $PIN 0
    fi
}

# Check to see if a pin # argument has been supplied!
function check_pinarg() {
    if [ -z "$1" ]; then
        echo "No GPIO pin specified, exiting!"
        usage ${UTYPE}
        exit 1
    fi
}

# Check to see if a pin state argument has been supplied!
function check_statearg() {
    if [ -z "$1" ]; then
        echo "No GPIO pin STATE specified, exiting!"
        usage ${UTYPE}
        exit 1
    fi
}

# Check to see if a pin state argument has been supplied!
function check_dirarg() {
    if [ -z "$1" ]; then
        echo "No GPIO pin DIR specified, exiting!"
        usage ${UTYPE}
        exit 1
    fi
}

# check to see if we are running as sudo (root), if not, bail!
function check_root() {
    if ! id | grep -q root; then
        echo "must be run as root"
        exit 1
    fi
}

# END of functions.sh


