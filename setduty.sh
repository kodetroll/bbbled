#!/bin/bash
# PERIOD of 100 is 20 mhz
PERIOD=1000
DUTY=100
# dc * period = period - duty
# (dc * period) - period = -duty
# period - (dc * period) = duty

function calc_percent () {
# duty cycle = (period-duty)/period
    if [ -z "$1" ]; then
        DT=$(($PERIOD/10))
    else
        DT=$1
    fi
    PER=$(($PERIOD-$DT))
    PER=$(($PER*100/$PERIOD))
    FREQ=$((100000000/$PERIOD))
}

#calc_percent

#echo "Duty Cycle: $PER %"
#echo "Modulation Freq: $FREQ"
echo "Setting Period to '$PERIOD'"
#echo "Setting Duty to '$DUTY' ($PER%)"

DUTYCYCLE=$1
echo "Duty Cycle: $DUTYCYCLE %"
L=$(($DUTYCYCLE * $PERIOD / 100))
echo "L: $L"
DUTY=$(( $PERIOD - $L ))
calc_percent DUTY
echo "Setting Duty to '$DUTY' ($PER%)"

echo "Duty Cycle: $PER %"
echo "Modulation Freq: $FREQ"

PIN=P8_13
PWMPIN=bone_pwm_${PIN}

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

