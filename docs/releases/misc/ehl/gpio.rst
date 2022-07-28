PCH GPIO Driver
---------------

PCH GPIO controller is primarily use for pin mux the SOC pads with several IO devices.
The Zephyr IA GPIO driver provide user to configure some of these pins as general purpose IOs.
The pin mux is completely controlled by BIOS and the Zephyr GPIO driver can configure/control only those pins 
which are not associated/muxed with any other peripherals.

GPIO driver supports following features:

-  Pins can be configured as either input or as output pins
-  Generate interrupt for level as well as edge trigger

Please note that The GPIO pin configuration by default is locked for safety reason 
by BIOS and the expectation is that user should modify the BIOS code to 
configure the GPIOs accordingly to their board design/use case. For testing purpose 
user can unlock all GPIOs from BIOS menu (Not safe).
	 
RTOS API Reference
~~~~~~~~~~~~~~~~~~

`Please refer Zephyr GPIO documentation for more details. <https://docs.zephyrproject.org/2.7.0/reference/peripherals/gpio.html>`_


Build Configuration
~~~~~~~~~~~~~~~~~~~

Add the following configurations in the sample prj.conf file:

::

   CONFIG_GPIO=y
   CONFIG_INTEL_GPIO=y
The GPIO sample application shows the following PCH General-Purpose I/O (GPIO)
features:

-  GPIO as an input to trigger the interrupt to the Host CPU

Hardware Setup
~~~~~~~~~~~~~~

On the CRB,

-  Connect **J1E2 header pin #13** (GPIO27) with **J1E2 header pin #17**
   (GPIO28).

In the BIOS menu,

1. Select **Intel Advanced Menu > PCH-IO Configuration > Security Configurations > Force unlock  > Enable**.
   Note: GPIO pin configuration by default is locked for safety reason by BIOS
2. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > GPIO0/TGPIO0 > None**, if it is not selected by
   default.
3. Select **GPIO0/TGPIO0 Mux Selection > All pins are GPIO**, if it is not selected by default.
4. Go to the **GPIO0/TGPIO0 Pin Selection** menu. Uncheck **GPIO27 [ ]** and **GPIO28 [ ]**, if these are checked by default.
5. Select **GPIO1/TGPIO1 > None**, if it is selected by default.
6. Select **GPIO1/TGPIO1 Mux Selection > All pins are GPIO**, if it is not selected by default.

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Find the sample application in the **zephyr-ia/samples/intel/gpio/** code base.

2. Build the sample code using following build command

.. code:: c

   west build -p -b ehl_crb ../zephyr-ia/samples/intel/gpio/


Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

   GPIO Test Sample App

   Toggling pin 23
   Pin 4 triggered
   Toggling pin 23
   Toggling pin 23
   Pin 4 triggered
   Toggling pin 23
   Toggling pin 23
   Pin 4 triggered
   Toggling pin 23
   Toggling pin 23
   Pin 4 triggered
   Toggling pin 23
   Toggling pin 23
   Pin 4 triggered
