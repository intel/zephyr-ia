UART Driver
-----------

**The UART controller supports following software features:**

-  Polling to receive and transmit single characters
-  Polling to receive and transmit single buffers
-  Asynchronous I/O programming using UART interrupts
-  Asynchronous direct memory access (DMA)-enabled transmit and receive
   capabilities
-  Asynchronous unsolicited receive capability (you will be notified
   when the UART port receives data)
-  Asynchronous receive with timeouts
-  Loopback operation
-  RS-485 standard-enabled transfers (half-duplex and full-duplex modes
   with polarity configuration)

Build Configuration
~~~~~~~~~~~~~~~~~~~

Add one or more following configurations in the sample prj.conf file for enable various UART features:

::

   CONFIG_SERIAL=y
   CONFIG_UART_INTEL=y
   CONFIG_UART_INTERRUPT_DRIVEN=y
   CONFIG_UART_LINE_CTRL=y
   CONFIG_UART_RS_485=y

The UART sample application demonstrates the following software features:

-  Polling mode read/write
-  Fifo mode read/write

Hardware Setup
~~~~~~~~~~~~~~

The sample application uses **UART_1 (J3C1 header)** as a test
interface. Use **RS-232-to-USB adapters** for interfacing between
the Development Machine and the headers.

Set up the hardware using the following steps:

1. Enable the **UART1** interface in the BIOS settings.
2. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > Uart1 >Host owned with pin muxed**
3. Connect the console header to a standard DB9 connector using a custom
   cable.

For this UART sample application, you need to set up terminal console
connected to UART_1 for user inputs and user-expected entries.

To run the sample application, set up the UART test console (UART_1) with following settings:

-  Baudrate: 115200
-  Data Bit: 8
-  Parity: None
-  Stop Bit: 1
-  Flow Control: None

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Find the sample application in the **zephyr-ia/samples/intel/uart/** code base.

2. Build the sample code using following build command

.. code:: c

   west build -p -b ehl_crb ../zephyr-ia/samples/intel/uart/

Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

The following is the **UART_2 console output**:

::

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

The following is the **UART_1 console output (test console)**:

::

   EUART FIFO DATA OUT

.. raw:: latex

   \newpage
