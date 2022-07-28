Time-Aware GPIO (TGPIO) Driver
------------------------------

A Time-Aware GPIO (TGPIO) is a variant of the GPIO that provides the
following extra features:

-  Pulse and waveform generation on the output pins
-  Pulse width modulation
-  Recording the time at which specific events occur
-  Event counters to record input events

There are two instances of the TGPIO block in the Intel® PSE. Each
instance has 20 TGPIO controllers. The TGPIOs are multiplexed with the
GPIOs. The GPIOs are in two groups of 30 pins, and the TGPIOs can be
allocated to drive the top 20, lower 20, or top 10, and lower 10 GPIO
pins. For more information on pin multiplexing, refer to the GPIO Pin Multiplexer Configuration section below.

Operating Modes
~~~~~~~~~~~~~~~

The TGPIO can be used in the following modes. The mode can be selected
by calling the associated API for that mode. The API
**tgpio_pin_periodic_out** is used to set the output mode. The APIs
**tgpio_pin_timestamp_event** and **tgpio_pin_count_events** are for
setting the input mode.

**Output Mode**

In this mode, the controller generates an output signal on a pin. The following are the necessary values to be set:

a. Pulse Width Stretch - how long the pulse should stay high
b. Start Time - time to start generating pulses
c. Interval - time interval between two consecutive pulses
d. Timer - the reference timer that the pin operates on
e. Pin Number - the pin that generates pulses
f. Repeat Count - number of times the event should repeat

**Input Mode (Event Count-based)**

In this mode, the controller is programmed to receive input signals and raise an interrupt only when a certain number of events occurs on the pin. When the ceiling is 1, it is similar to the simple input mode. The following are the necessary values to be set:

a. Timer - the reference timer that the pin operates on
b. Input Event Polarity - rising, falling, or toggle edges
c. Event Count - ceiling for events for generating an interrupt
d. Pin Number - the pin that receives pulses

.. raw:: latex

   \newpage

**Input Mode (Time-based)**

The TGPIO pins are multiplexed with the GPIO pins. A set of twenty GPIO pins can be assigned to the TGPIO according to the following order.

The following are multiplexer setting and owner for the GPIO pins per instance:

a. Pinmux 0 - All pins are in the GPIO mode
b. Pinmux 1 - GPIO pins 10 to 29 are in the TGPIO mode
c. Pinmux 2 - GPIO pins 0 to 19 are in the TGPIO mode
d. Pinmux 3 - GPIO pins 0 to 9 and 20 to 29 are in the TGPIO mode


GPIO Pin Multiplexer Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The TGPIO pins are pin-muliplexed with the GPIO pins. A set of 20 GPIO pins can be assigned to the TGPIO according to the following order:

The following are multiplexer setting and owner for the GPIO pins per instance:

-  Pinmux 0 - All pins are in the GPIO mode
-  Pinmux 1 - GPIO pins 10 to 29 are in the TGPIO mode
-  Pinmux 2 - GPIO pins 0 to 19 are in the TGPIO mode
-  Pinmux 3 - GPIO pins 0 to 9 and 20 to 29 are in the TGPIO mode

Please note that GPIO here is PSE GPIO controller and not the PCH GPIO controller. Currently there is no support for PSE GPIO controller for IA Zephyr.

RTOS API Reference
~~~~~~~~~~~~~~~~~~

The TGPIO interface for the Processor platform can be accessed via
the Zephyr\* TGPIO driver interface. The APIs are described in **zephyr-iotg/include/drivers/gpio-timed.h**

.. _build-configuration-8:

Build Configuration
~~~~~~~~~~~~~~~~~~~

To build the TGPIO sample application, refer to the following build time
configurations:

-  CONFIG_GPIO=y: Enables the GPIO pin in Zephyr\* RTOS, values allowed
   are y and n
-  CONFIG_GPIO_TIMED_INTEL=y: Enables the Intel® PSE TGPIO driver, values
   allowed are y and n

The TGPIO sample application shows you the following features:

-  Rate adjustment for timers
-  Offset adjustment for timers
-  Different modes of input and output for TGPIO pins
-  Setting and viewing the current time on timers

Hardware Setup
~~~~~~~~~~~~~~

On the CRB,

-  Connect **J1E2 header pin #13** (TGPIO27) with **J1E2 header pin
   #17** (TGPIO28) as a loopback route to test the time-based input and
   unlimited output scenario, event ceiling input and unlimited output scenario.

In the BIOS menu,

1. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > Eclite > disabled**, if it is enabled by default.
2. Select **Intel Advanced Menu > PCH-IO Configuration > Security Configurations > Force unlock  > Enable**.
3. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > GPIO0/TGPIO0 > Host owned with pin muxed**.
4. Select **GPIO0/TGPIO0 Mux Selection > TOP**.
5. Select the **GPIO0/TGPIO0 Pin Selection** menu, and check **TGPIO27 [x]**, if it is not selected by default.
6. Select the **GPIO0/TGPIO0 Pin Selection** menu, and check **TGPIO28 [x]**.

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Run the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-   Find the sample code in the **zephyr-ia/samples/intel/tgpio/** code base.

-   Use the below west build command to build the sample application

.. code:: c

     west build -p auto -b ehl_crb ../zephyr-ia/samples/intel/tgpio/

Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

   Bind success [TGPIO_0]

   Test for time adjustment
   -------------------------
   [TGPIO_0] Timer: 0, Time Now: 100:860, Adding 99999896 nsecs
   [TGPIO_0] Timer: 0, Adjust Done, Added 99999896 nsecs, Time Now: 100:606040106

   Test for rate adjustment
   -------------------------
   [TGPIO_0] Pin: 28, Timer: 1, Scheduled at:00000101:00000000
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101: 99974735][ec - 2], running slow with 2000 nsecs
   [TGPIO_0] Adjusting TMT_0 frequency
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:199974451][ec - 3], running slow with 284 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:299974451][ec - 4], running fast with 0 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:399974450][ec - 5], running slow with 1 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:499974450][ec - 6], running fast with 0 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:599974449][ec - 7], running slow with 1 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:699974449][ec - 8], running fast with 0 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:799974448][ec - 9], running slow with 1 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:899974448][ec - 10], running fast with 0 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -101:999974447][ec - 11], running slow with 1 nsecs
   [cb-TGPIO_0] adj_freq: [pin -27][ts -102: 99974452][ec - 12], running fast with 5 nsecs

   Test for cross timestamp
   -------------------------
   [TGPIO_0] Timer: 0, Local Time: 00000102:120742912, Ref. Time: 00000018:91121351

   Test for unlimited output and timebased input
   -----------------------------------------------
   [TGPIO_0] Pin: 28, Timer: 0, Scheduled at:00000101:09544580
   [TGPIO_0] Pin: 27, Timer: 0, Scheduled at:00000101:15488345

   Test for unlimited output and event ceiling input
   ---------------------------------------------------
   [TGPIO_0] Pin: 28, Timer: 0, Scheduled at:00000101:31757245
   [TGPIO_0] Pin: 27, Timer: 0, Scheduled at:00000101:31757245

   [cb-TGPIO_0][pin -27][ts -101: 40757285][ec -10]
   [cb-TGPIO_0][pin -27][ts -101: 50757285][ec -20]
   [cb-TGPIO_0][pin -27][ts -101: 60757285][ec -30]
   [cb-TGPIO_0][pin -27][ts -101: 70757285][ec -40]
   [cb-TGPIO_0][pin -27][ts -101: 85757285][ec -55]
   [cb-TGPIO_0][pin -27][ts -101: 95757285][ec -65]
   [cb-TGPIO_0][pin -27][ts -101:105757285][ec -75]
   [cb-TGPIO_0][pin -27][ts -101:115757285][ec -85]
   [cb-TGPIO_0][pin -27][ts -101:125757285][ec -95]
   [cb-TGPIO_0][pin -27][ts -101:140757285][ec -110]
   [cb-TGPIO_0][pin -27][ts -101:150757285][ec -120]
   [cb-TGPIO_0][pin -27][ts -101:160757285][ec -130]
   [cb-TGPIO_0][pin -27][ts -101:170757285][ec -140]
   [cb-TGPIO_0][pin -27][ts -101:180757285][ec -150]
   [cb-TGPIO_0][pin -27][ts -101:195757285][ec -165]
