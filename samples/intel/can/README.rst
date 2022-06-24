.. _pse_can:

PSE CAN
###########

Overview
********
A simple CAN  example for ehl_crb board.
This test application perform tests for CAN functionalities-
RX/TX operations in various operational modes like Normal, FD,
and extended.

Building and Running
********************
Standard build and run procdure defined for ehl_crb target to be
followed.

Sample Output
=============
*** Zephyr EFI Loader ***
Zeroing 4833376 bytes of memory at 0x10c000
Copying 32768 data bytes to 0x1000 from image offset
Copying 49152 data bytes to 0x100000 from image offset 32768
Copying 2113440 data bytes to 0x5a8060 from image offset 81920
Jumping to Entry Point: 0x112b (48 31 c0 48 31 d2 48)
*** Booting Zephyr OS build zephyr-v2.7.0-7-gb1916959f03b  ***
CAN Test Application

CAN set Internal loopback  mode

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

Perform cleanup

Detaching 2 Filters
Exiting CAN App.

.. code-block:: can
