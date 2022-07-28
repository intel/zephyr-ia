Pulse Width Modulation (PWM) Driver
-----------------------------------

The Pulse Width Modulation (PWM) controller generates a pulsing
electrical signal that alternates between the on and off states on a
repeated basis. The period and duty cycle of the pulse can be configured
using the PWM controller registers.

The Intel® Zephyr IA PWM IP consists of the following features:

-  Support for two instances of PWM controller
-  Up to eight programmable timers per instance
-  Non-configurable timer width of 32 bits
-  Support for two operation modes (free-running and user-defined count)
-  Support for independent clocking of timers
-  Configurable polarity for each individual interrupt
-  Configurable option to include the timer toggle output (toggles
   whenever the timer counter reloads)
-  Configurable option to enable the programmable pulse-width modulation
   of the timer toggle outputs


RTOS API Reference
~~~~~~~~~~~~~~~~~~

For more information, go to the `Zephyr* Project
website <https://docs.zephyrproject.org/2.7.0/reference/peripherals/pwm.html>`__


Build Configuration
~~~~~~~~~~~~~~~~~~~

To build the PWM as part of the Zepyhr\* RTOS, enable the following
configuration flags:

-  CONFIG_PWM=y: Enables the PWM in the Zephyr\* RTOS
-  CONFIG_PWM_INTEL=y: Enables the Intel® Zephyr IA PWM mode driver

The PWM sample application is compatible with the CRB’s **PWM or TGPIO header
(J1E2)**.

Hardware Setup
~~~~~~~~~~~~~~

In the BIOS menu, set up the hardware using the following steps:

1. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > Eclite > disabled**, if it is enabled by default.
2. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > PWM > Host owned with pin muxed**, if it is not selected by default.
3. Select the **PWM Pin Mux Selection** menu, check **PWM0 [x]**, if it
   is not checked by default.
4. Select the **PWM Pin Mux Selection** menu, check **PWM2 [x]**, if it
   is not checked by default.

For PWM waveform viewing, connect an oscilloscope to probe **pin #1** and **pin #3** on the **J1E2** header to see the PWM signal from the PWM0 and PWM2 channels.

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Find the sample application in the **zephyr-ia/samples/intel/pwm/** code base.

2. Build the sample code using following build command

.. code:: c

   west build -p -b ehl_crb ../zephyr-ia/samples/intel/pwm/

Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

   PWM_0 - Bind Success
   Running rate: 100000000
   Configured pin 0 (Period: 20, pulse: 5)
   Configured pin 2 (Period: 20, pulse: 10)
