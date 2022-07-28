Time-Sensitive Networking
-------------------------

Intel® Zephyr IA GbE is a Quality-of-Service (QoS) network controller that
consists of basic Ethernet and Time-Sensitive Networking (TSN)
capabilities.

TSN is a set of standards developed by the TSN task group within the
IEEE 802.1 working group to enable deterministic real-time communication
over the Ethernet. The following are two important components in TSN:

-  Time synchronization
-  Traffic shaping

For time synchronization, GbE driver support the IEEE 802.1AS generic
Precision Time Protocol (gPTP) clock synchronization stack, including
the IEEE 1588v2 Ethernet frame receive and transmit timestamping
capability.

For traffic shaping, the Intel® IA GbE driver supports the launch time or
transmit time (Time-based scheduling).


RTOS API Reference
~~~~~~~~~~~~~~~~~~

For more information on Zephyr\* networking stack APIs related to TSN,
refer to the following links:

-  `generic Precision Time Protocol
   (gPTP) <https://docs.zephyrproject.org/2.7.0/reference/networking/gptp.html>`__

-  `Precision Time Protocol (PTP)
   format <https://docs.zephyrproject.org/2.7.0/reference/networking/ptp_time.html>`__

-  `Traffic
   Classification <https://docs.zephyrproject.org/2.7.0/reference/networking/traffic-class.html>`__

-  `BSD
   Sockets <https://docs.zephyrproject.org/2.7.0/reference/networking/sockets.html?highlight=bsd%20socket>`__

-  `Ethernet
   Management <https://docs.zephyrproject.org/2.7.0/reference/networking/ethernet_mgmt.html>`__

The sample application shows the capability of time-based scheduling,
also known as the launch time or transmit time. The application
transmits User Datagram Protocol (UDP) packets according to parameter
settings.

Hardware Setup
~~~~~~~~~~~~~~

Connect the CRB Intel® PSE GbE1 port back-to-back to any Linux\* Host that
has a generic PTP (gPTP) time synchronization-capable GbE port (e.g. i210).

Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Build the sample code using following command:

.. code:: c

  west build -p -b ehl_crb samples/net/sockets/txtime -- -DOVERLAY_CONFIG=../../../../../zephyr-ia/samples/intel/ethernet/txtime/overlay-ehl.conf

Make sure to configure the packet interval time to validate the TBS using CONFIG_NET_SAMPLE_PACKET_INTERVAL, which is in milliseconds.

After loading the application, it start send UDP packets in the configured interval.
 
Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

Open a terminal in the Linux pair board to start time synchronization for the TSN sample
application using the following command:

::

   ptp4l -ml 6 -f gptp_m1512_rgmii_1Gb.cfg -i eth0

**gptp_m1512_rgmii_1Gb.cfg**:

::

   [global]
   gmCapable 1
   priority1 248
   priority2 248
   logAnnounceInterval 0
   logSyncInterval -3
   syncReceiptTimeout 3
   neighborPropDelayThresh 800
   min_neighbor_prop_delay -20000000
   assume_two_step 1
   path_trace_enabled 1
   follow_up_info 1
   transportSpecific 0x1
   ptp_dst_mac 01:80:C2:00:00:0E
   network_transport L2
   delay_mechanism P2P
   ingressLatency 231
   egressLatency 147
   
Ingress and egress Latencies were picked from the `Linux Ethernet TSN GSG <https://cdrdv2.intel.com/v1/dl/getContent/616446>`_ .
At the movement this values represent the Marvell 1512 PHY placed in EHL CRB.
   

Open another terminal in Linux to capture UDP packets sent from the TSN sample
application using the following command:

::

   tcpdump -Q in -j adapter_unsynced --time-stamp-precision=nano -s 64 -B 512 -vvvXXni enp0s29f1 udp port 4242 -w tbstest.pcap -c 1000

Note: Linux pair suppose to have a logical ip address in order to receive the UDP packet. So make sure to configure
ipv4 or ipv6 address for the link partner

Open the tbstest.pcap using wireshark and can see the time difference between the packets being sent from EHL zephyr. It should match with what is configured in the EHL zephyr build config.
