SBL Native Boot setup
=====================

Developer prerequisites
-----------------------

Developer should be familer with SBL (Slim Bootloader) and please refer `SBL documentation <https://slimbootloader.github.io/getting-started/index.html>`_ if you are new to SBL.

Obtain SBL Source code
-------------------

Downlaod SBL source using following command:

 ::
 
   git clone https://github.com/slimbootloader/slimbootloader.git
   git checkout 3112989fdcec8240857b96c942d9942ec0e18254
	
Generate SblKeys
----------------

Generate SBL keys using following command:

 ::
   
   python3 slimbootloader/BootloaderCorePkg/Tools/GenerateKeys.py -k <SblKeys Folder>
   export SBL_KEY_DIR = <SblKeys Folder>

Create SBL OS image
-------------------

Build your Zephyr sample apps. Following command can be used for build Zephyr hello world sample:

::

   west build -p -b ehl_crb samples/hello_world/
  
Copy zephyr.efi file to tools folder in slimbootloader/BootloaderCorePkg/Tools and generate **sbl_os** file using following commands:

::

   objcopy -O elf32-i386 build/zephyr/zephyr.elf slimbootloader/BootloaderCorePkg/Tools/zephyr32.elf
   python <Tools>/GenContainer.py create -cl ZEPR:<Tools>zephyr32.elf -k <SblKeys>/OS1_TestKey_Priv_RSA3072.pem -o sbl_os



Copy PSE Firmware in <SBL source> and Build SBL for Elkhart Lake platform
-------------------------------------------------------------------------
For generate PSE FW::
  
  west init -m https://github.com/intel/pse-fw
  west update
  cd ehl_pse-fw
  ./build.sh apps/samples/<sample app>

Copy PSE Firmware and Build SBL for Elkhart Lake platform using following commands:

::

  cp PseFw.bin slimbootloader/Platform/ElkhartlakeBoardPkg/Binaries/.
  python BuildLoader.py build ehl
  
Please refer `SBL for Elkhart Lake platform <https://slimbootloader.github.io/supported-hardware/ehl-crb.html>`_ for more details.

Please refer PSE SDK user guide for more details on PSE FW SDK and build.

Generate SBL Binary
-------------------

Run following command for stiching SBL with IFWI image::

   python Platform/ElkhartlakeBoardPkg/Script/StitchLoader.py -i <input IFWI Image> -s Outputs/ehl/SlimBootloader.bin -o <out sbl IFWI image>

You can obtain `input IFWI Image <https://cdrdv2.intel.com/v1/dl/getContent/737578/737719?filename=Elkhart_Lake_Platform_CRB_IFWI_v4275_00.zip>`_ from Intel RDC portal.

Configuration Editor Tool
-------------------------

SBL supports a `Configuration Editor Tool (ConfigEditor.py) <https://slimbootloader.github.io/tools/ConfigTools.html>`_ to configure firmware settings with graphics UI. This tool is included in SBL source package at BootloaderCorePkg/Tools.

Running Configuration Editor from SblPlatform folders and this will open config UI:

::

   python3 slimbootloader/BootloaderCorePkg/Tools/ConfigEditor.py
  
After that, user needs to load the YAML file along with DLT(Delta)file for the Elkhart Lake CRB board into the ConfigEditor, change the desired configuration values.
Please refer `Configuration Editor Tool (ConfigEditor.py) <https://slimbootloader.github.io/tools/ConfigTools.html>`_ for more details.
 
The YAML file is located at slimbootloader/Platform/ElkhartlakeBoardPkg/CfgData/CfgDataDef.yaml and the DLT file is located at 
"slimbootloader/Platform/ElkhartlakeBoardPkg/CfgData/CfgData_Ext_IotgCrb.dlt"

Make required changes for IO Module in Silicon Settings. In OS Boot options, Select Boot Option 0, Then change software partition to 0 and File system to FAT.

Save the changes to dlt file by selecting “Save Config Changes to Delta file”.

Save the dlt file as “Autogen_CfgData_Ext_IotgCrb.dlt” in folder slimbootloader/Outputs/ehl.

Copy follwing files from <Tools> folder to slimbootloader/Outputs/ehl:
      - GenCfgData.py
      - CfgDataTool.py
      - IfwiUtility.py
      - CommonUtility.py
      - SingleSign.py

DLT file be the inputs to the stitch tool so that new config changes can be merged and stitched into the final configuration.
Use following commands to stitch config changes to IFWI binary.

::

    python3 slimbootloader/Outputs/ehl/CfgDataStitch.py -i <input_sbl_binary> -t . -k <SblKeys>/ConfigTestKey_Priv_RSA3072.pem -c slimbootloader/Outputs/ehl/ -o <output_sbl_binary>

Once the above script ran successfully, the new configurations are stitched to input_ifwi(outimage.bin).
Now <output_sbl_binary> can be flashed on to ehl_crb board.

Configurations for IO modules
-----------------------------

After loading CfgDataDef.yaml, click on file menu and select Load Config changes from Delta option then select CfgData_Int_IotgRvp1.dlt

Following section will provide configuration details for various IO devices which are default not enabled:

UART(RS232/RS485)
~~~~~~~~~~~~~~~~~

In silicon settings:
::

   PCH PSE HSUART instance 0 &1 -> Host owned(0x02)


SPI
~~~
::

    PSE Add-In-Card -> Enabled
    SPI 0 & 1-> Host owned.(0x02)
    SPI0 CS0 & CS1 -> Enabled (0x02)
    SPI1 CS0 & CS1 -> Enabled (0X02)

DMA
~~~
::

    DMA 0 -> PSE owned (0x01)
    DMA 1 & 2 -> Host owned (0x02,0x02)

GPIO
~~~~
::
 
    Unlock All GPIO pads → Enable
    TGPIO 0 :None
    TGPIO 0 MUX SELECTION : All pins are GPIO(0x00)
    TGPIO 0 Pin selection -> 27, 28 pins unchecked(count from 0 to 27th, 28th hex value and change them to 0x00) 
    TGPIO 1 :None
    TGPIO 1 MUX SELECTION : All pins are GPIO(0x00)

TGPIO
~~~~~
::

    TGPIO 0 : Host owned
    TGPIO 0 MUX SELECTION : TOP (0x01)
    TGPIO 0 Pin selection -> 27 & 28 checked (count from 0 to 27th, 28th hex value and change them to 0x01)
    TGPIO 1 :Host owned
    TGPIO 1 MUX SELECTION : TOP (0x01)

Create Zephyr boot USB Pen drive
--------------------------------

Format a USB pendrive with FAT32 file system and then create a folder namly 'boot' in it. Copy the "sbl_os" image previously generated into the 'boot' folder.
Plug the USB pen drive into one of the USB ports in the CRB and then power on CRB. This will boot Zephyr image.
