Gigabit Ethernet (GbE) Driver Interface
---------------------------------------

Device Overview and Supported Features
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Intel® Zephyr IA firmware contains GbE driver to enable basic functions of three
Gbe instances. Out of all three Gbe devices, two were placed in the Intel® PSE and 3rd one placed in
default PCH.

The following features are enabled in the GbE driver:

-  Multiple transmitter and receiver queues support (configurable for
   each direction, up to a maximum of eight)
-  Reduced Gigabit Media-Independent Interface (RGMII) PHY interface support for
   Marvell’s 88E1512.
-  Management Data Input/Output (MDIO) bus communication support for
   clause-22 and clause-45
-  TCP/IP/User Datagram Protocol (UDP) hardware checksum offloading
-  Media Access Control (MAC) address perfect and hash filtering
-  MAC address runtime re-configuration support
-  IEEE 1588v2 transmitter and receiver packets timestamping support
-  Precision Time Protocol (PTP) clock and frequency, and support for
   rate adjustment configuration


RTOS API Reference
~~~~~~~~~~~~~~~~~~

The Zephyr\* networking stack APIs used for interacting with the GbE
driver are explained in the following Zephyr\* Project links:

-  `BSD
   Sockets <https://docs.zephyrproject.org/2.7.0/reference/networking/sockets.html#bsd-sockets-interface>`__
-  `Ethernet <https://docs.zephyrproject.org/2.7.0/reference/networking/ethernet.html>`__
-  `Networking <https://docs.zephyrproject.org/2.7.0/reference/networking/index.html>`__
-  `Networking 
   Modules <https://docs.zephyrproject.org/apidoc/2.7.0/group__networking.html>`__


Build Configuration
~~~~~~~~~~~~~~~~~~~

The following build configuration is required for basic GbE functions:

-  CONFIG_ETH_DWC_EQOS=y: Enables the GbE MAC driver, values allowed are
   y or n
-  CONFIG_ETH_PHY_MARVELL=y and CONFIG_ETH_PHY_88E1512=y: Enable the
   Marvell\* 1512 PHY driver, values allowed are y or n
-  CONFIG_ETH_PHY_GEN_PHY=y: Enables the Generic PHY driver, values
   allowed are y or n
-  CONFIG_ETH_DWC_EQOS_0=y: Enables Intel® PSE GbE port 0, values
   allowed are y or n
-  CONFIG_ETH_DWC_EQOS_1=y: Enables Intel® PSE GbE port 1, values
   allowed are y or n
-  CONFIG_ETH_DWC_EQOS_2=y: Enables Intel® PCH GbE port 2, values
   allowed are y or n
-  CONFIG_ETH_DWC_EQOS_TX_QUEUES=2: Sets transmitter queues number to be
   used, values allowed are from 1 to 8
-  CONFIG_ETH_DWC_EQOS_RX_QUEUES=2: Sets receiver queues number to be
   used, values allowed are from 1 to 8
-  CONFIG_ETH_DWC_EQOS_DMA_RING_SIZE=16: Set transmitter or receiver per
   queue DMA ring entries, values allowed are from 4 to 1024


PHY Interface Selection (RGMII)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The official IFWI binary release’s default setting is the SGMII PHY for PCH GbE
and RGMII PHY interface for both Intel® PSE GbE.

A list of networking samples is available on the `Zephyr*
project <https://docs.zephyrproject.org/2.7.0/samples/net/net.html>`__
page. Intel selects the **Echo Server** sample application for
demonstration.

Echo Server is a TCP/UDP Server that receives a message from the TCP/UDP
Client and then replies the same message back to the Client, acting as
an echo. The **Processor CRB** is selected as the Server while the
**Linux\* Host** is selected as the Client.

UDP connection is selected because it is very simple and direct to
demonstrate.

.. note:: The Echo Server TCP connection requires the application to be rerun whenever the Client needs to reconnect to the TCP session.


The configuration parameters to the application are as follows:

-  IPv4 address of the Echo Server
-  IPv4 address of the Client
-  UDP/TCP Server port number (hardcoded with the value 4242)
-  UDP/TCP maximum message length (hardcoded with the value 1280)

.. raw:: latex

   \newpage

Hardware Setup
~~~~~~~~~~~~~~

You should program the MAC address for GBE. Refer following document for more details:

`Programming the Intel Atom® x6000E Series Processors, Intel® Pentium® and Celeron® N and J 
Series Processors (Code name: Elkhart Lake) MAC Address using Capsule
Update <https://cdrdv2.intel.com/v1/dl/getContent/620481?explicitVersion=true>`__

Set up the hardware using the following steps:

1. Select Intel Advanced Menu > PCH-IO Configuration > PSE Configuration > GBE. Toggle the default setting to “Host owned with pin muxed”

Please refer section "Configurations for IO modules" in `SBL Native Boot setup <slim_bootloader.rst>`_  for details on device configuration with SBL boot.

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Find the Echo Server sample application at **zephyr/samples/net/sockets/echo_server/**.

2. Edit the **prj.conf** file in
   **zephyr/samples/net/sockets/echo_server** to add the following configuration to enable the Ethernet ports.

   ::

      CONFIG_ETH_DWC_EQOS_INTEL_PSE_PLATDATA=y
      CONFIG_ETH_PHY=y
      CONFIG_ETH_PHY_USE_C22=y
      CONFIG_ETH_PHY_USE_C45=y
      CONFIG_ETH_PHY_MARVELL=y
      CONFIG_ETH_PHY_88E1512=y
      CONFIG_ETH_DWC_EQOS=y

      CONFIG_ETH_DWC_EQOS_DMA_RING_SIZE=16
      CONFIG_ETH_DWC_EQOS_IRQ_MODE=y

      CONFIG_ETH_DWC_EQOS_1_PCI=y
      CONFIG_ETH_DWC_EQOS_1=y
      CONFIG_ETH_DWC_EQOS_1_IRQ_DIRECT=y
      CONFIG_ETH_DWC_EQOS_1_NAME="ETH_DWC_EQOS_1"
      CONFIG_ETH_DWC_EQOS_1_AUTONEG=y

      CONFIG_PM_SERVICE=n

      CONFIG_NET_L2_ETHERNET=y


      # Change IP address for the server to 192.0.2.1
      CONFIG_NET_CONFIG_MY_IPV4_ADDR="192.0.2.1"

      # Change IP address for the client to 192.0.2.2
       CONFIG_NET_CONFIG_PEER_IPV4_ADDR="192.0.2.2"

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Build the sample code using following build command

.. code:: c

    west build -p -b ehl_crb samples/net/sockets/echo_server/ -- -DOVERLAY_CONFIG=../../../../../zephyr-ia/samples/intel/ethernet/echo_server/overlay-ehl.conf

Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

**Execute these commands in the Linux\* Host to set up a UDP
connection:**

.. code:: c

   # Set static IP 192.0.2.2 for Ethernet port
   # which connected to EHL CRB PSE GbE port 1
   sudo ifconfig <Ethernet_Port_Interface_Name> 192.0.2.2

   # Start UDP connection with EHL PSE using nc command
   # NOTE: EHL has IP 192.0.2.1 and listens to port 4242
   nc -u 192.0.2.1 4242


Expected Output
~~~~~~~~~~~~~~~
To test, type some text (any text) on the Linux\* Host CRB terminal. You
will see a response from the Linux\* and Zephyr serial output terminal.
