.. _pse_uart:

PSE Uart
###########

Overview
********
A simple PSE UART  example for ehl_crb board.
Tests UART for polled and interrupt based operation.
Application assumes that tests executes on UART_PSE_1.
This application can be built into modes:

* single thread
* multi threading

Building and Running
********************
Standard build and run procdure defined for ehl_crb target to be
followed.

Sample Output
=============
UART Test Application
Testing Device UART_PSE_1

Testing Polled Mode on UART_PSE_1
Testing uart_poll_in , press ENTER on test port
uart_poll_in passed.Received
Testing uart_poll_out
uart_poll_out Passed
Testing uart tx fifo fill on UART_PSE_1
Passed
Testing uart irq rx
Waiting for character on UART_PSE_1
Callack triggered for UART_PSE_1
Rx_length =1
Data=1
Passed
Exiting UART App.
.. code-block:: console
