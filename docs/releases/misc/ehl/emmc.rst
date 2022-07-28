EMMC Driver
-----------

The eMMC driver supports the following feature:

-	Supports only DDR50 mode/speed with maximum 52Mhz clock.
-	SDMA support 
-	Transfers the data in 1-bit, 4-bit and 8-bit mode.
-	Support 64-bit address.
-	Supports necessary disk driver interface to enable the FATFS file system to read/write to a file.

RTOS API Reference
~~~~~~~~~~~~~~~~~~

`Please refer Zephyr File System interface for more details. <https://docs.zephyrproject.org/2.7.0/reference/file_system/index.html?highlight=fatfs>`_

Build Configurations
~~~~~~~~~~~~~~~~~~~~

Enable the following configurations in order to use the eMMC driver with Zephyr FAT file system:

::

   CONFIG_DISK_ACCESS=y
   CONFIG_EMMC_INTEL=y
   CONFIG_FILE_SYSTEM=y
   CONFIG_FAT_FILESYSTEM_ELM=y

In order to format the volume to FAT_FS 32 while mounting enable the following configuration.
CONFIG_FS_FATFS_MOUNT_MKFS=y

By default, the eMMC bus width is set to 8-bit mode, in order to change the bit mode to 1 or 4 the following configuration needs to be used. If the bus width is set to 1-bit only SDR mode is supported.
CONFIG_EMMC_BUS_WIDTH=4


The eMMC controller supports following software features:

-	Uses the disk driver interface to enable the FATFS file system.
-	Supports Zephyr File system APIs to read, write to a file or directory.
-	Transfers the data in DDR50 mode when bus width is configured to 4-bit or 8-bit.
-	Transfers the data in SDR mode when bus width is configured to 1-bit.

The File system sample application demonstrates use of the filesystem API and uses the FAT file system driver to mount an eMMC card. This example depicts how to use eMMC with the Zephyr disk and file system APIs:

-	Read sector size and memory size using the disk IOCTL API.
-	Set the Line control width using the disk IOCTL API.
-	File open, write and read APIs using FATFS file system.

Hardware Setup
~~~~~~~~~~~~~~
	
There is no external hardware setup required for eMMC.

Build and Load The Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-	Find the sample code in the zephyr-ia/samples/intel/emmc/

-   Use the below west build command to build the sample application

.. code:: c

     west build -p auto -b ehl_crb ../zephyr-ia/samples/intel/emmc/
   
Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

        Sector size 512
        Memory Size(MB) 30352
        Disk mounted.
        Creating new file /SD:/testfile.txt
        Opened file /SD:/testfile.txt
        File now exists /SD:/testfile.txt
		Data written:"sample app for emmc!"
        Data successfully written!
        Listing dir /SD: ...
        [FILE] TESTFILE.TXT (size = 20)
        Data read:"sample app for emmc!"
        Data read matches data written
        Exiting eMMM sample app.
