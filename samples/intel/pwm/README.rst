.. _pwm_test:

Test for PWM
###########

Overview
********
This is a sample PWM application for the EHL-CRB board.
This test verifies the APIs for PWM IP

To validate the output in PWM mode, you need to connect the oscilloscope
to pin3 on PWM_0.

Building and Running
********************
Standard build procedure.

Sample Output
=============

*** Booting Zephyr OS build v2.6.0-rc3-4-g9d6e435e9595  ***
PWM_0 - Bind Success
Running rate: 100000000
Configured pin 0 (Period: 20, pulse: 5)
Configured pin 2 (Period: 20, pulse: 10)
