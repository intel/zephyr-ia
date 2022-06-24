.. _GPIO:

GPIO
####

Overview
********
A simple GPIO example for ehl_crb board.
This application needs connection between two pins. GPIO_COM_0_B pin 28 is used
as output and pin 27 as input pin. While output pin is toggled, the input pin will
generate an interrupt and call callback function defined in sample app. The
callback function prints out a log to show it entered into callback.

Building and Running
********************
Standard build and run procdure defined for ehl_crb target to be
followed.

Sample Output
*************

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

.. code-block:: GPIO
