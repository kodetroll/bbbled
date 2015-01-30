#!/bin/bash
# pwm.sh - A script that sets the PWM pin to the specified values
# A good example of the actual calls to get pwm going.
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

# PERIOD of 100 is 20 mhz
PERIOD=20000000
DUTY=10000000
PER=$(($PERIOD-$DUTY))
PER=$(($PER*100/$PERIOD))
FREQ=$((100000000/$PERIOD))
echo "Duty Cycle: $PER %"
echo "Modulation Freq: $FREQ"
echo "Setting Period to '$PERIOD'"
echo "Setting Duty to '$DUTY' ($PER%)"

PWM_PIN_NAME=`./get_pwm_pin_name ${PIN}`
PWMPIN="bone_pwm_${PWM_PIN_NAME}"

echo "PIN: $PIN"
echo "PWM_PIN_NAME: $PWM_PIN_NAME"
echo "PWMPIN: $PWMPIN"

CAPEMGR=`ls -d /sys/devices/bone_capemgr.*`
#SLPATH=`ls -d /sys/devices/bone_capemgr.* | awk -F '.' '{print $2}'`
SLOTS=${CAPEMGR}/slots

echo "Capemgr Path: $CAPEMGR"
echo "Slot Path: $SLOTS"
#exit 0

# find ocp #
OCP=`ls -d /sys/devices/ocp.*`
echo "OCP Path: $OCP"

echo "Requesting PWM from Slots"
echo am33xx_pwm > $SLOTS

# find pwm #
PWMPATH="$OCP/pwm_test_$PWM_PIN_NAME.*"
echo "PWM Path: $PWM"

if [ -d "$PWMPATH" ]; then
    echo "PWM already Slotted!"
else
    echo "Requesting PWM Pin '$PWM_PIN_NAME' from Slots"
    echo ${PWMPIN} > $SLOTS
fi

# find pwm #
PWM=`ls -d $OCP/pwm_test_$PWM_PIN_NAME.*`
echo "PWM Path: $PWM"

#exit 0


echo "Setting Period to '$PERIOD'"
echo ${PERIOD} > ${PWM}/period
echo "Setting Duty to '$DUTY' ($PER%)"
echo ${DUTY} > ${PWM}/duty

# Done
