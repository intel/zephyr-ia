**IA Zephyr - Elkhart Lake R4.3 Release Note**
=====================================================================
We are pleased to announce the release of IA Zephyr for Elkhart Lake.

Major Features include driver/BSP support for following devices/components:

* PSE DMA Controller
* PCH GPIO Controller
* PSE UART/RS485 Controller
* PSE TGPIO Controller
* PSE PWM Controller
* PSE SPI Controller
* eMMC Controller
* IPC controller
* PSE CAN controller
* PSE and PCH GBE TSN controller
* Host HECI Stack
* Sample Applications for IO drivers 

Supported Zephyr version: 2.7.2 

.. note:: Additional patches from Intel were added on top of Zephyr 2.7.2 mainline code for CAN/UART/SPI driver interfaces/APIs and FS. Please refer `intel Zephyr repo <https://github.com/intel/zephyr/commits/intel-ehl-ia>`__ for more details on these commits)

Supported IFWI version: `MR3 IFWI <https://cdrdv2.intel.com/v1/dl/getContent/726728/727243?filename=Elkhart_Lake_Platform_CRB_IFWI_v4122_00.zip>`__

**Please note that these drivers/BSP is only a reference source code with Alpha quality and not expected use directly in any products.**


Development system requirements and prerequisites
-------------------------------------------------

`Please refer development <misc/ehl/common.rst>`_ and `setup prerequisites <misc/ehl/common.rst>`_ for more details.

Install the dependencies
------------------------

Follow the Getting Started guide on Zephyr’s public site: https://docs.zephyrproject.org/2.7.0/getting_started/index.html

* When you reach step 3.2, instead of doing `west init`, do the following

.. code:: c

     git clone https://github.com/intel/zephyr-ia.git zephyr-ia
     west init -l zephyr-ia
     west update

* Continue with installing toolchain (if not already done).

Build the Sample Application
----------------------------

* To build hello world sample, you can run following west command from "zephyr" folder:

.. code:: c

     cd zephyr
     west build -p auto -b ehl_crb samples/hello_world
    
To build any reference IO driver Sample provided under "/zephyr-ia/samples/intel" folder, you can run following command:

.. code:: c

    west build -p auto -b ehl_crb ../zephyr-ia/samples/intel/<reference_driver>

Where <reference_driver> is the folder name of sample application. For example "uart" for uart sample application.

Once build completed, you can find zephyr binaries/images under "build/zephyr" folder

The -p auto option automatically cleans by-products from a previous build if necessary, which is useful if you try building another sample. 

In case build fail, then please try to rebuild after delete the "zephyr/build" folder.

Run the Sample Application on Target System
-------------------------------------------

Please refer following Zephyr documenation for more details on booting Zephyr on Elkhart Lake CRB:

https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html

Please refer `SBL Native Boot setup <misc/ehl/slim_bootloader.rst>`_  for details of loading Zephyr with Slim Bootloader.


Driver supported features/limitations and sample app details
------------------------------------------------------------

`General information and prerequisites <misc/ehl/common.rst>`_

`DMA driver and sample app <misc/ehl/dma.rst>`_

`GPIO driver and sample app <misc/ehl/gpio.rst>`_

`UART/RS485 driver and sample app <misc/ehl/uart.rst>`_

`TGPIO driver and sample app <misc/ehl/tgpio.rst>`_

`PWM driver and sample app <misc/ehl/pwm.rst>`_

`SPI driver and sample app <misc/ehl/spi.rst>`_

`eMMC driver and sample app <misc/ehl/emmc.rst>`_

`CAN driver and sample app <misc/ehl/can.rst>`_

`HECI stack and sample app <misc/ehl/heci.rst>`_

`Ethernet driver and NW sample app <misc/ehl/gbe.rst>`_

`TSN driver and sample app <misc/ehl/tsn.rst>`_
