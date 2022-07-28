Direct Memory Access (DMA) Driver
---------------------------------

Zephyr IA supports three DMA controllers. Please note that by default DMA controller 0 is used by PSE FW and only controller 1 and 2 multiplexed  for Host.

Following features are supported:

-  Eight channels in each controller
-  Linked-list mode and direct mode
-  Hardware DMA handshake mode for peripherals
-  The DMA controller can transfer data between memory to memory
-  32-bit and 64-bit addressing

**RTOS API Reference**

Refer to the Zephyr* RTS DMA interface at the `Zephyr* RTOS
website <https://docs.zephyrproject.org/2.7.0/reference/peripherals/dma.html>`__.


**Build Configuration**

.. note::
   Ensure following BKM while using DMA:

   1. Set buffer memories to be 32-byte aligned: E.g. `static u8_t write_enable[] __attribute__((aligned(32))) = { 0x06 };`

   2. Clean the cache before writing to the buffer: E.g. `arch_dcache_range(buff, BUFF_SIZE, K_CACHE_WB);`

   3. After reading the buffer, invalidate the cache: E.g. `arch_dcache_range(buff, RX_BUFF_SIZE, K_CACHE_INVD);`

Enable the following macros to use the DMA mode:

::

 CONFIG_DMA=y
 CONFIG_DMA_INTEL=y


To allocate a DMA channel statically, Intel® Zephyr IA offers a channel
allocation solution.

Users and drivers can use macros indicating the configuration, rather
than hardcoding in the firmware.

E.g. The SPI driver can use the following macro to configure SPI0 and
I2C1 for the following usage: SPI0 transmitter uses DMA channel 12, the
receiver uses channel 14 and 15, SPI1 receiver and transmitter do not
use DMA:

::

  CONFIG_SPI0_TX_USE_DMA=y
  CONFIG_SPI0_TX_DMA_CHAN=12
  CONFIG_SPI0_RX_USE_DMA=y
  CONFIG_SPI0_RX_DMA_CHAN=14
  CONFIG_SPI0_RX_DMA_CHAN_EXT=y
  CONFIG_I2C0_RX_DMA_CHAN_EXT=15
  CONFIG_SPI1_TX_USE_DMA=n
  CONFIG_SPI1_TX_USE_DMA=n
  
The DMA sample application shows you the basic usage of direct memory
access (DMA) with the Zephyr\* API, which includes the following features:

-  Basic DRAM to DRAM memory direct copy
-  Basic DRAM to DRAM linked list memory copy

Hardware Setup
~~~~~~~~~~~~~~

There is no external hardware setup required.

In the BIOS menu:

1. Select **Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > DMA1/DMA2 > Host owned with pin muxed**, if it is not   selected by default.

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load The Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-	Find the sample code in the **zephyr-ia/samples/intel/dma/** code base.

-   Use the below west build command to build the sample application:

.. code:: c

     west build -p auto -b ehl_crb ../zephyr-ia/samples/intel/dma/


Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

   testing DMA normal reload mode

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   DMA transfer done
   potato
   DMA Passed

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   reload block 1
   DMA transfer done
   likes
   potato
   DMA Passed

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   reload block 1
   reload block 2
   DMA transfer done
   horse
   likes
   potato
   DMA Passed

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   reload block 1
   reload block 2
   reload block 3
   DMA transfer done
   my
   horse
   likes
   potato
   DMA Passed

   testing DMA linked list mode

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   DMA transfer done
   block count = 1
   potato
   DMA Passed

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   DMA transfer done
   block count = 2
   likes
   potato
   DMA Passed

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   DMA transfer done
   block count = 3
   horse
   likes
   potato
   DMA Passed

   Preparing DMA Controller: Chan_ID=0, BURST_LEN=8
   Starting the transfer
   DMA transfer done
   block count = 4
   my
   horse
   likes
   potato
   DMA Passed

.. raw:: latex

   \newpage
