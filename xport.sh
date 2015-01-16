#!/bin/bash
# xport.sh - A script to remove the specified GPIO pin from the export map.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
# Based on code from http://www.circuidipity.com/bbb-led.html
#
# usage: xport gpio#, e.g. 'xport 44'

GPIO="/sys/class/gpio"

function usage () {
    echo "Usage: $0 <GPIO#>"
}

# check to see if we are running as sudo (root), if not, bail!
if ! id | grep -q root; then
        echo "must be run as root"
        exit
fi

if [ -z "$1" ]; then
    echo "No GPIO pin specified, exiting!"
    usage
    exit 0
fi

echo $1 > $GPIO/export
