SPI Driver
----------

A Serial Peripheral Interface (SPI) is a four-wire, bi-directional
serial bus that provides a simple and efficient method of transmitting
data over a short distance between many devices. For transfer rates above
16 Mbps, Intel recommends using Direct Memory Access (DMA). An SPI is
used for connecting the Intel® PSE to the external sensor devices 
(e.g. combo accelerometers, gyroscopes, and compass devices). The SPI driver
supports the following:

-  Four SPI instances
-  Multiple connected target
-  Four combinations of polarity and phase (also known as modes)
-  Full-duplex and half-duplex modes of operation
-  Programmable SPI clock frequency
-  FIFO register of 64 bytes with programmable watermarks or thresholds
-  DMA, Interrupt and polled mode
-  Programmable frame width (8/16 bits)
-  Programmable clock phase (delay or no delay)
-  Programmable clock polarity (high or low)

.. note::

Limitations of SPI in interrupt mode:

-  Loopback mode not supported.
-  Maximum frequency supported is 6MHz.
-  Maximum word size can transfer at a time is 64

Limitations of SPI in polled mode:

- Maximum frequency supported is 6MHz.

For DMA mode, maximum frequency validated is up to 10MHz

To enable **SPI interrupt mode** use following configs in prj.conf:

 CONFIG_SPI_INTEL_USE_DMA=n
 
 CONFIG_SPI_INTEL_POLLED_MODE=n


RTOS API Reference
~~~~~~~~~~~~~~~~~~

For more information on the Zephyr\* SPI interface, refer to the
`Zephyr* Project
website <https://docs.zephyrproject.org/2.7.0/reference/peripherals/spi.html>`__.


Build Configuration
~~~~~~~~~~~~~~~~~~~

The following is the build configuration:

-  CONFIG_SPI=y
-  CONFIG_SPI_INTEL=y

You can test the Serial Peripheral Interface (SPI) sample applications
provided in the SDK code tree.

Hardware Setup
~~~~~~~~~~~~~~

No hardware setup required for loopback(internal) sample application.

In the BIOS menu,

-  Configure the SPI0 interface to “Host owned” by selecting **Intel
   Advanced Menu > PCH-IO Configuration > PSE Configuration > SPI0 > Host
   owned with pin muxed**, if it is not configured by default.

You can test the Serial Peripheral Interface (SPI) sample applications
provided in the SDK code tree.

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-   Find the sample code in the **zephyr-ia/samples/intel/spi/spi_loopback/** code base.

-   Use the below west build command to build the sample application

.. code:: c

     west build -p auto -b ehl_crb ../zephyr-ia/samples/intel/spi/spi_loopback/


Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

   Running test suite test_spi
   ===================================================================
   START - test_spi_loopback
   I: SPI test on buffers TX/RX 0x5ad3e0/0x598020
   I: SPI test slow config
   I: Start complete multiple
   I: CS control inhibited (no GPIO device)
   I: Passed
   
   ....
	
   I: All tx/rx passed
   PASS - test_spi_loopback in 0.86 seconds
   ===================================================================
   Test suite test_spi succeeded
   ===================================================================
   PROJECT EXECUTION SUCCESSFUL
