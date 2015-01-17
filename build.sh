#!/bin/bash
g++ enable_clocks.cpp -o enable_clocks
#
# run with 'sudo ./enable_clocks -e 1 2 3' to enable all three EHRPWMs
# (fails third pwm)
