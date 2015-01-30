#!/bin/bash
# pwm_init.sh - A script that initializes the specified PWM pin prior
# to use by oither scripts.
#
# (C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries
#
# Author: Kodetroll
# Date: January 2015
#
UTYPE="<PIN#>"
. ./functions.sh

# check to see if we are running as sudo (root), if not, bail!
check_root

# Sleep time (blink on/off time)
TIME=2

PIN=$1
# Check to see if a valid pin# argument has been supplied
check_pinarg $PIN

echo "PIN: $PIN"

# PERIOD of 100 is 20 mhz
PERIOD=20000000
DUTY=10000000
PER=$(($PERIOD-$DUTY))
PER=$(($PER*100/$PERIOD))
FREQ=$((100000000/$PERIOD))
#echo "Duty Cycle: $PER %"
#echo "Modulation Freq: $FREQ"
#echo "Setting Period to '$PERIOD'"
#echo "Setting Duty to '$DUTY' ($PER%)"

PWM_PIN_NAME=`./get_pwm_pin_name ${PIN}`
PWMPIN="bone_pwm_${PWM_PIN_NAME}"

echo "PWM_PIN_NAME: $PWM_PIN_NAME"
echo "PWMPIN: $PWMPIN"

CAPEMGR=`ls -d /sys/devices/bone_capemgr.*`

echo "Capemgr Path: $CAPEMGR"

SLOTS=${CAPEMGR}/slots

echo "Slot Path: $SLOTS"

# find ocp #
OCP=`ls -d /sys/devices/ocp.*`
echo "OCP Path: $OCP"

echo "Requesting PWM from Slots"
echo am33xx_pwm > $SLOTS

# find pwm #
PWMPATH="./testsysfs $OCP/pwm_test_$PWM_PIN_NAME.* 0"
echo "PWM Path: $PWMPATH"

if [ "$PWMPATH" = "1" ]; then
    echo "PWM already Slotted!"
else
    echo "Requesting PWM Pin '$PWM_PIN_NAME' from Slots"
    echo ${PWMPIN} > $SLOTS
fi

# find pwm #
PWM=`ls -d $OCP/pwm_test_$PWM_PIN_NAME.*`
echo "PWM Path: $PWM"

echo "Setting Period to '$PERIOD'"
echo ${PERIOD} > ${PWM}/period
echo "Setting Duty to '$DUTY' ($PER%)"
echo ${DUTY} > ${PWM}/duty
echo "Setting PWM Channel '$PWM_PIN_NAME' to RUN"
echo 1 > ${PWM}/run

# Done
