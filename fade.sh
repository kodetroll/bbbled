#!/bin/bash
UP="10 20 30 40 50 60 70 80 90 100"
DN="90 80 70 60 50 40 30 20 10 1"

while [ 1 ]; do
    for DC in $UP; do
#        echo $DC
        ./setduty.sh ${DC}
    done
    for DC in $DN; do
#        echo $DC
        ./setduty.sh ${DC}
    done
done
