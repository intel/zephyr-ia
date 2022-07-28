Controller Area Network (CAN) Driver
------------------------------------

CAN is a serial communication protocol that supports distributed
real-time control. CAN can be used in noise-prone environments because
of its differential nature in physical layer signals. The CAN with
Flexible Data-rate (CAN FD) is an enhancement to the CAN protocol.

CAN FD has the following two features compared to CAN:

-  The extended user data rate is from 8 to 64 bytes
-  The ability to send user data with higher data rates

The two features ensure that higher bandwidth use cases are fulfilled
while profiting from the experiences in the CAN development.

The Intel® Zephyr IA instantiates two instances of the CAN bus that support
both CAN 2.0 Specification A and B (ISO 11898-1) and communication
according to the CAN FD Protocol Specification 1.0.

The CAN IP supports the following features:

-  CAN FD with up to 64 data bytes
-  Hardware-based acceptance filtering
-  Programmable loop-back test mode
-  Bit-rate switching for CAN FD
-  Parity protection for the message RAMs with error injection
   functionality
-  The Standard/Extended CAN maximum bit rate is 1 Mbps while the CAN FD
   bus speed scaling supports up to 5 Mbps


RTOS API Reference
~~~~~~~~~~~~~~~~~~

The CAN interface for the Processor platform can be accessed via the
Zephyr\* RTOS CAN driver interface API described in **zephyr/include/drivers/can.h** 


Build Configuration
~~~~~~~~~~~~~~~~~~~

To build the CAN sample application, refer to the following build time
configurations:

-  CONFIG_CAN=y: Enables the CAN in Zephyr\* RTOS, values allowed are y or n
-  CONFIG_CAN_INTEL=y: Enables the Intel® Zephyr IA CAN driver, values allowed
   are y or n
-  CONFIG_FD_MODE=n: Enables the CAN FD mode, values allowed are y or n. To test
   normal mode this config should be disabled
-  CONFIG_CAN_IOCTL=y: Enables the CAN I/O Control (IOCTL) interface,
   values allowed are y or n
-  CONFIG_CAN_DISABLE_AUTO_RETRANSMIT=n: Disables auto retransmit for
   transmission failures,values allowed are y or n

For more information on the CAN, please refer to the `Zephyr* Project
website <https://docs.zephyrproject.org/2.7.0/reference/networking/can_api.html?highlight=controller%20area%20network%20can>`__.

The CAN sample application shows the following features:

-  Controller Area Network (CAN) bit rate selection
-  Defining and attaching filters to the interrupt handlers
-  CAN Flexible Data Rate (FD) operation
-  CAN standard and extended identifier usage
-  Detaching filters

This sample application does the following:

-  Sends a standard frame with CANID 0x1 on CAN0 and receives the same
   frame on CAN0.
-  Sends and receives CAN FD frames with CANID 0x2 at the 500-kbps
   nominal bit rate and 1-mbps fast bit rate.

Hardware Setup
~~~~~~~~~~~~~~

The sample application relies on an internal loop-back routing.

Configure the following to allocate CAN0:

1. I2C7 and CAN0 share same function, to assign CAN0 to host owned I2C7 should be assigned to host owned.
2. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > Eclite > disabled**, if it is enabled by default.
3. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > I2C7 > Host owned with pin muxed**
   in the BIOS settings.
4. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > CAN0 > Host owned with pin muxed**
   in the BIOS settings.

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load The Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Find the sample application in the **zephyr-ia/samples/intel/can/** code base.

2. Build the sample code using following build command

.. code:: c

   west build -p -b ehl_crb ../zephyr-ia/samples/intel/can/

Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

   CAN Test Application

   CAN set Internal loopback mode

   CAN set bit rate

   Configure filters for STD CAN frames
   Configuring Std filter id 1 Success ret = 0!!

   Transmit STD CAN frames on CAN 0
   inside send std message

   ******RX STD callback ******

   -----Received Message----

   TimeStamp = 23da

   ID: 1
   Type: 0
   RTR: 0
   id: 1
   DLC: 8
   DATA[0]: 0x1 DATA[1]: 0x2 DATA[2]: 0x3 DATA[3]: 0x4
   DATA[4]: 0x5 DATA[5]: 0x6 DATA[6]: 0x7 DATA[7]: 0x8

   End of RX STD CALLABCK

   CAN send success !!

   Configure filters for Extended CAN frames
   Configuring Ext filter id ffff1 Success ret = 0!!

   Transmit EXT CAN frames on CAN 0

   -----Received Message----

   TimeStamp = 4b0c

   ID: ffff1
   Type: 1
   RTR: 0
   id: ffff1
   DLC: 8
   DATA[0]: 0x1 DATA[1]: 0x2 DATA[2]: 0x3 DATA[3]: 0x4
   DATA[4]: 0x5 DATA[5]: 0x6 DATA[6]: 0x7 DATA[7]: 0x8

   CAN EXT send success !!

.. |CAN Pinout Setup| image:: images/can_connection.JPG
