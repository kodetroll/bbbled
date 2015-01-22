
#!/bin/bash
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

PIN=P8_13
PWMPIN=bone_pwm_${PIN}
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
PWMPATH=$OCP/pwm_test_$PIN.*
echo "PWM Path: $PWM"

if [ -d "$PWMPATH" ]; then
    echo "PWM already Slotted!"
else
    echo "Requesting PWM Pin '$PIN' from Slots"
    echo ${PWMPIN} > $SLOTS
fi

# find pwm #
PWM=`ls -d $OCP/pwm_test_$PIN.*`
echo "PWM Path: $PWM"

#exit 0


echo "Setting Period to '$PERIOD'"
echo ${PERIOD} > ${PWM}/period
echo "Setting Duty to '$DUTY' ($PER%)"
echo ${DUTY} > ${PWM}/duty

