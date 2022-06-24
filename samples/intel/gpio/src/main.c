/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file
 * @brief Sample Application for GPIO driver.
 * This sample shows how to configure gpio pins to output direction to
 * control pin levels, and also how to configure pins to input direction
 * to trigger interrupts.
 * The sample uses 2 pins, one as output pin, and the other
 * as input pin. Connect these 2 pins, output pin will toggle the level,
 * this would trigger interrupts for the input pin.
 *
 * @brief Hardware setup.
 * Connect pins 13 and 17 of J1E2 header of EHL CRB board in loopback.
 *
 * @{
 */

/* Local Includes */
#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/gpio.h>

/* GPIO output pin device used for this sample */
#define GPIO_OUT_DRV_NAME "GPIO_COM_0_B"
/* GPIO input pin device used for this sample */
#define GPIO_IN_DRV_NAME "GPIO_COM_0_B"
/* GPIO output pin number used for this sample */
#define GPIO_OUT_PIN (23)
/* GPIO input pin number used for this sample */
#define GPIO_INT_PIN (4)

/* Input gpio pin callback function */
void gpio_callback(const struct device *port, struct gpio_callback *cb,
		   uint32_t pins)
{
	printk("Pin %d triggered\n", GPIO_INT_PIN);
}

/* GPIO callback while trigger interrupt */
static struct gpio_callback gpio_cb;

int main(int argc, char *argv[])
{
	const struct device *gpio_out_dev, *gpio_in_dev;
	int ret = -1;
	int toggle = 1;

	printk("GPIO Test Sample App\n");

	/* Get the device handle for GPIO device by 'GPIO_OUT_DRV_NAME' */
	gpio_out_dev = device_get_binding(GPIO_OUT_DRV_NAME);
	if (!gpio_out_dev) {
		printk("Cannot find %s!\n", GPIO_OUT_DRV_NAME);
		return ret;
	}

	/* Get the device handle for GPIO device by 'GPIO_IN_DRV_NAME' */
	gpio_in_dev = device_get_binding(GPIO_IN_DRV_NAME);
	if (!gpio_in_dev) {
		printk("Cannot find %s!\n", GPIO_IN_DRV_NAME);
		return ret;
	}

	/* GPIO Pin configuration
	 * GPIO PIN DIRECTION    : Output
	 */

	ret = gpio_pin_configure(gpio_out_dev, GPIO_OUT_PIN, (GPIO_OUTPUT));
	if (ret) {
		printk("Error configuring pin %d!\n", GPIO_OUT_PIN);
		return ret;
	}

	/** The GPIO pin configuration by default is locked for safety reason
	 *  by BIOS and the expectation is that customer/user should modify
	 *  the BIOS code to configure the GPIOs accordingly to their board
	 *  design/use case. For testing purpose user can unlock all GPIOs
	 *  from BIOS menu before running this sample code
	 */
	ret = gpio_pin_configure(gpio_in_dev, GPIO_INT_PIN, GPIO_INPUT);

	if (ret) {
		printk("Error configuring pin %d!\n", GPIO_INT_PIN);
		return ret;
	}
	ret = gpio_pin_interrupt_configure(gpio_in_dev, GPIO_INT_PIN,
				(GPIO_INPUT | GPIO_INT_EDGE_RISING));
	/* Init user callback function */
	gpio_init_callback(&gpio_cb, gpio_callback, BIT(GPIO_INT_PIN));

	/* Add user callback with the GPIO device */
	ret = gpio_add_callback(gpio_in_dev, &gpio_cb);
	if (ret) {
		printk("Cannot setup callback!\n");
		return ret;
	}

	while (1) {
		printk("Toggling pin %d\n", GPIO_OUT_PIN);
		/* Toggle the output pin */
		if (toggle) {
			ret = gpio_port_set_bits_raw(gpio_out_dev, BIT(GPIO_OUT_PIN));
		} else {
			ret = gpio_port_clear_bits_raw(gpio_out_dev, BIT(GPIO_OUT_PIN));
		}
		if (ret) {
			printk("Error set pin %d!\n", GPIO_OUT_PIN);
			return ret;
		}

		if (toggle) {
			toggle = 0;
		} else {
			toggle = 1;
		}

		k_sleep(K_SECONDS(2));
	}
}

/**
 * @}
 */
