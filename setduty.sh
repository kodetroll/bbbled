#!/bin/bash
# setduty.sh - A script to set the dutycycle of a specified PWM pin.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
#
# Usage: 'setduty.sh <PIN#> <DUTYCYCLE>"
#
UTYPE="<PIN#> <DUTYCYCLE>"
. ./functions.sh

# PERIOD of 100 is 20 mhz
PERIOD=1000
DUTY=100

PIN=23

# check to see if we are running as sudo (root), if not, bail!
#check_root

#echo "Duty Cycle: $PER %"
#echo "Modulation Freq: $FREQ"
echo "Setting Period to '$PERIOD'"
#echo "Setting Duty to '$DUTY' ($PER%)"

if [ -z "$2" ]; then
	DUTYCYCLE=1
else
	DUTYCYCLE=$2
fi

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

PWM_PIN_NAME=`./get_pwm_pin_name ${PIN}`
PWMPIN="bone_pwm_${PWM_PIN_NAME}"

echo "PIN: $PIN"
echo "PWM_PIN_NAME: $PWM_PIN_NAME"
echo "PWMPIN: $PWMPIN"

echo "Duty Cycle: $DUTYCYCLE %"
L=$(($DUTYCYCLE * $PERIOD / 100))
echo "L: $L"
DUTY=$(( $PERIOD - $L ))
calc_percent DUTY
echo "Setting Duty to '$DUTY' ($PER%)"

echo "Duty Cycle: $PER %"
echo "Modulation Freq: $FREQ"

# find ocp #
OCP=`ls -d /sys/devices/ocp.*`
echo "OCP Path: $OCP"

# find pwm #
PWM=`ls -d $OCP/pwm_test_$PIN.*`
echo "PWM Path: $PWM"

calc_percent DUTY

#echo "Setting Duty to '$DUTY' ($PER%)"
#echo 10 > ${PWM}/duty

echo "Setting Duty to '$DUTY' ($PER%)"
echo ${DUTY} > ${PWM}/duty

echo "Setting Period to '$PERIOD'"
echo ${PERIOD} > ${PWM}/period

echo "Setting PWM Channel '$PIN' to RUN"
echo 1 > ${PWM}/run

