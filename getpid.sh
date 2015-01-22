#!/bin/bash
if [ -z "$1" ]; then
    echo "No process name supplied, exiting!"
    exit 1
fi
pid=`ps hax | grep ttyO0 | grep $1 | awk -F ' ' '{print $1}'`
echo $pid
exit 0
