.. _fat_fs:

FAT Filesystem Sample Application using eMMC
############################################

Overview
********

This sample app demonstrates use of the filesystem API and uses the FAT file
system driver to mount an on-chip eMMC card.

Requirements
************

This project requires eMMC card formatted with FAT filesystem.
See the :ref:`disk_access_api` documentation for Zephyr implementation details.

Building and Running
********************

Standard build and run procdure defined for ehl_crb target to be
followed.

Sample output
=============

.. code-block:: console
        *** Booting Zephyr OS build v2.6.0-rc3-4-g9d6e435e9595  ***
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
