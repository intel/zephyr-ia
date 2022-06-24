/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Sample Application for PWM
 * This example demonstrates the following
 * Derive the clock rate for the PWM device
 * Generate the PWM output by setting the period and pulse width
 * in terms of clock cycles
 * Generate the PWM output by setting the period and pulse width
 * in microseconds
 * @{
 */

/* Local Includes */
#include <sys/printk.h>
#include <sys/util.h>
#include <drivers/pwm.h>
#include <stdio.h>
#include <toolchain/gcc.h>
#include <zephyr.h>

/** PWM channel 1. Each PWM controller has 8 PWM channels */
#define PWM_CHANNEL_1 0
/** PWM channel 2 */
#define PWM_CHANNEL_2 2
/** Device name for PWM controller 0 */
#define PWM_0_NAME "PWM_0"
/** time period of 20 micro seconds */
#define PERIOD_20_USEC 20
/** time period of 15 micro seconds */
#define PULSE_15_USEC 15
/** time period of 10 micro seconds */
#define PULSE_10_USEC 10
/** time period of 5 micro seconds */
#define PULSE_5_USEC 5
/** time period of 20 HW clock cycles */
#define PERIOD_HW_CYCLES 20
/** time period of 5 HW clock cycles */
#define PULSE_HW_CYCLES 5

/* @brief main function
 * PWM Sample Application for PSE
 * The sample app tests the PWM IP
 * The user is required to connect a probing device like oscilloscope on
 * pin1 on PWM_0 and pin3 on PWM_0 to check the PWM output.
 * Also can connect the AIC card to drive the motor via PWM14.
 */
void main(void)
{
	const struct device *pwm_0;
	uint64_t cl;
	int ret;
	uint8_t pwm_flag = 0;

	/* Get the device handle for PWM instance  */
	pwm_0 = device_get_binding(PWM_0_NAME);
	if (!pwm_0) {
		printk("%s - Bind failed\n", PWM_0_NAME);
		return;
	}
	printk("%s - Bind Success\n", PWM_0_NAME);

	/* Gets the clock rate(cycles per second) for the PWM device */
	ret = pwm_get_cycles_per_sec(pwm_0, 0, &cl);
	if (ret != 0) {
		printk(" Get clock rate failed\n");
		return;
	}
	printk("Running rate: %lld\n", cl);

	/* Set the period and pulse width of the PWM output in terms
	 * of clock cycles. Expected output -Pulse with 25% duty cycle
	 */
	ret = pwm_pin_set_cycles(pwm_0, PWM_CHANNEL_1, PERIOD_HW_CYCLES,
				 PULSE_HW_CYCLES, pwm_flag);
	if (ret != 0) {
		printk("Pin set cycles failed\n");
		return;
	}

	printk("Configured pin %d (Period: %d, pulse: %d)\n", PWM_CHANNEL_1,
	       PERIOD_HW_CYCLES, PULSE_HW_CYCLES);

	k_sleep(K_MSEC(1000));

	/* Set the period and pulse width of the PWM output in
	 * micro seconds. Expected output-Pulse with 50% duty cycle
	 */
	ret = pwm_pin_set_usec(pwm_0, PWM_CHANNEL_2,
			       PERIOD_20_USEC, PULSE_10_USEC, pwm_flag);
	if (ret != 0) {
		printk("Pin set usec failed\n");
		return;
	}
	printk("Configured pin %d (Period: %d, pulse: %d)\n", PWM_CHANNEL_2,
	       PERIOD_20_USEC, PULSE_10_USEC);

	while (1) {
		k_sleep(K_MSEC(100));
	}

}
