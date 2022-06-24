/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Sample Application for UART (Universal Asynchronous
 * Receiver/Transmitter) driver.
 * This example demonstrates how to use the UART for the following I/O
 * operations:
 *    • Polled Write
 *    • Polled Read
 *    • fifo_fill
 *    • fifo_read
 * @{
 */

/* Local Includes */
#include <sys/printk.h>
#include <string.h>
#include <drivers/uart.h>
#include <zephyr.h>

/** UART driver used for data transmit/receive. */
#define UART_DEV "UART_PSE_1"
#define UART_RS_485_DEV "UART_PSE_0"

/** Set timeout in micro seconds */
#define DEFAULT_TIMEOUT K_MSEC(30000)

/** define semaphore for data transmit */
static K_SEM_DEFINE(tx_sem, 0, 1);
/** define semaphore for data receive */
static K_SEM_DEFINE(rx_sem, 0, 1);

#ifdef CONFIG_UART_RS_485
#define UART_RS_485_AT_NS (100)
#define UART_RS_485_DT_NS (100)
#define UART_RS_485_DE_RE_TAT_NS (500)
#define UART_RS_485_RE_DE_TAT_NS (500)
#endif

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
#define FIFO_DATA "UART FIFO DATA OUT\n"
#define MAX_READ_LEN (64)
#define UART_DELAY_MS K_MSEC(100)

static char rx_buff[MAX_READ_LEN];

/* Uart callback function. */
static void uart_callback_fn(const struct device *dev, void *user_data)
{
	int size;

	printk("Callack triggered for %s\n", dev->name);
	size = uart_fifo_read(dev, rx_buff, MAX_READ_LEN);
	rx_buff[size] = '\0';
	printk("Rx_length =%d\n", size);
	printk("Data=%s\n", rx_buff);
	uart_irq_rx_disable(dev);
	k_sem_give(&rx_sem);
}

/* @brief test_uart_fifo_fill
 * Fills fifo with specified data.
 */
static int test_uart_fifo_fill(const struct device *dev)
{
	int tx_size;

	printk("Testing uart tx fifo fill on %s\n", dev->name);
	tx_size = uart_fifo_fill(dev, FIFO_DATA, sizeof(FIFO_DATA));
	if (tx_size != sizeof(FIFO_DATA)) {
		printk("UART FIFO fill failed\n");
		printk("Wrote %x of %ld\n", tx_size, sizeof(FIFO_DATA));
		return -EIO;
	}

	/* Add delay to allow characters to be printed on uart console. */
	k_sleep(UART_DELAY_MS);
	printk("Passed\n");
	return 0;
}

/* @brief test_uart_irq_rx
 * Recevies data from specified uart device and stores in local fifo.
 */
static int test_uart_irq_rx(const struct device *dev)
{
	/* Set user callback for handling rx interrupt. */
	uart_irq_callback_set(dev, uart_callback_fn);
	printk("Testing uart irq rx\n");
	uart_irq_rx_enable(dev);
	printk("Waiting for character on %s\n", dev->name);
	if (k_sem_take(&rx_sem, DEFAULT_TIMEOUT)) {
		printk("IRQ rx timed out.\n");
		uart_irq_rx_disable(dev);
		return -EIO;
	}

	printk("Passed\n");
	return 0;
}
#endif

/* @brief test_polled_io
 * Does polled read and write on specified uart device.
 */
static int test_polled_io(const struct device *dev)
{
	char char_out = 'E';
	char char_in;

	printk("Testing Polled Mode on %s\n", dev->name);

	printk("Testing uart_poll_in , press ENTER on test port\n");
	while (uart_poll_in(dev, &char_in) < 0) {
		k_sleep(K_MSEC(100));

	}
	if (char_in != '\r') {
		printk("uart_poll_in failed\n");
		return -EIO;
	}

	printk("uart_poll_in passed.Received %c\n", char_in);

	printk("Testing uart_poll_out\n");
	uart_poll_out(dev, char_out);
	printk("uart_poll_out Passed\n");

	return 0;
}

#ifdef CONFIG_UART_RS_485
/* @brief test_rs_485
 * Config UART to UART 485 mode and performs polled I/O operation.
 */
static int test_rs_485(void)
{
	int ret;
	struct uart_rs_485_config config;
	const struct device *dev;

	dev = device_get_binding(UART_RS_485_DEV);
	if (dev == NULL) {
		printk("Failed to get dev binding for rs_485_dev\n");
		return -EIO;
	}

	printk("Testing RS485 on %s\n", dev->name);
	/* Configs for uart 485 mode */
	config.de_re_tat_ns = UART_RS_485_DE_RE_TAT_NS;
	config.re_de_tat_ns = UART_RS_485_RE_DE_TAT_NS;
	config.de_assertion_time_ns = UART_RS_485_AT_NS;
	config.de_deassertion_time_ns = UART_RS_485_DT_NS;
	config.transfer_mode = UART_RS485_XFER_MODE_HALF_DUPLEX;
	config.de_polarity = UART_RS485_POL_ACTIVE_HIGH;
	config.re_polarity = UART_RS485_POL_ACTIVE_LOW;
	ret = uart_rs_485_config_set(dev, &config);
	if (ret) {
		printk("RS485 config failed\n");
		return -EIO;
	}
	ret = uart_line_ctrl_set(dev, UART_LINE_CTRL_RS_485, true);
	if (ret) {
		printk("RS485 enable failed\n");
		return -EIO;
	}

	printk("Testing RS485 IO\n");

	ret = test_polled_io(dev);
	if (ret) {
		printk("RS-485 IO failed\n");
		return ret;
	}

	/* Setting TX only or RX only supported when operating in half duplex
	 * mode.
	 */
	if (config.transfer_mode == UART_RS485_XFER_MODE_HALF_DUPLEX) {
		ret = uart_drv_cmd(dev, UART_DRIVER_CMD_SET_RX_ONLY_MODE, true);
		if (ret) {
			printk("UART_DRIVER_CMD_SET_RX_ONLY_MODE failed\n");
			return ret;
		}

		ret = uart_drv_cmd(dev, UART_DRIVER_CMD_SET_TX_ONLY_MODE, true);
		if (ret) {

			printk("UART_DRIVER_CMD_SET_TX_ONLY_MODE failed\n");
			return ret;
		}
	}
	return 0;
}
#endif

/* @brief print exit msg
 * Prints UART sample app exit message.
 */
static inline void print_exit_msg(void)
{
	printk("Exiting UART App.\n");
}

/* @brief main function
 * The UART application demonstrates the polled I/O operations
 * and the fifo I/O operations.
 */
void main(void)
{

	const struct device *uart_dev = NULL;

	printk("UART Test Application\n");
	/* Get the device handle for UART device */
	uart_dev = device_get_binding(UART_DEV);

	if (!uart_dev) {
		printk("UART: Device driver not found\n");
		return;
	}

	printk("Testing Device %s\n\n", uart_dev->name);

	if (test_polled_io(uart_dev)) {
		print_exit_msg();
		return;
	}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	if (test_uart_fifo_fill(uart_dev)) {
		print_exit_msg();
		return;
	}

	if (test_uart_irq_rx(uart_dev)) {
		print_exit_msg();
		return;
	}
#endif

#ifdef CONFIG_UART_RS_485
	if (test_rs_485()) {
		printk("rs-485 test failed.\n");
	}
#endif

	print_exit_msg();
}
