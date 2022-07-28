Host Embedded Controller Interface (HECI) Stack
-----------------------------------------------

The Host Embedded Controller Interface (HECI) in the Intel® Zephyr IA platform provides 
a bi-directional fully asynchronous communication interface between the IA Zephyr Host software and the Intel® PSE
firmware. 

The following are goals of the HECI Client Message Link:
    
**Agnostic to Client protocols**

The HECI Client Message Link is agnostic to the message data that makes up the protocol between the PSE FW and the Intel® Zephyr IA client. It could generally be that the Host or the Intel® Zephyr IA clients’ protocol is encapsulated within the HECI message transport.

**Allows arbitrary Client message lengths**

The HECI Client Message Link allows for an arbitrary client message size. The maximum size of a client’s message is governed by the maximum buffer size supported by the client and the client’s protocols. A client’s message may be divided into smaller sub-messages during transmission through the HECI circular buffers.

**Provides Client enumeration and address assignment**

The HECI Client Message Link supports the ability for clients to perform certain bus functions, e.g. Intel® PSE FW client discovery, client address assignments, and client capability reporting.

**Provides a basic message flow control**

To ensure that a client’s received message buffer does not overflow, the HECI Client Message Link provides the basic flow control for the clients.

**Allows one Client pair’s traffic to flow independently without the others**

When one client is currently processing a received message and cannot accept other messages, it should not gate another client from sending and receiving messages through the HECI.

On the Host side (IA Zephyr), the HECI stack act as a communication protocol entity. These drivers handle messages from the Intel® PSE firmware with the IPC packet format and then send the client message and notify a certain client. Next, the drivers package the message from the client in the IPC format and send the message back to the Intel® PSE firmware.
The IPC driver handles the IPC hardware and packets.

Build Configuration
~~~~~~~~~~~~~~~~~~~

Add following configurations in the sample prj.conf file for enable HECI stack:

::

   CONFIG_IA_USER_APP_FRAMEWORK=y
   CONFIG_IPC_INTEL=y
   CONFIG_IPC=y
   CONFIG_HOST_IA_SERVICE=y
   CONFIG_SYS_MNG=y
   CONFIG_HECI=y
   CONFIG_NUM_USER_APP_AND_SERVICE=2
   CONFIG_SYS_IA_SERVICE=y

The HECI sample application shows how to use the host embedded controller
interface (HECI) to communicate with the Intel® Programmable Services
Engine (Intel® PSE) and Host (Zephyr IA). The sample application defines a client
that receives a message from the PSE (PSE FW version details).

Hardware Setup
~~~~~~~~~~~~~~

There is no specific external hardware setup required. For running the sample app,
you must update the PSE FW also with HECI PSE sample app (see below build and load section for more details).


Build and Load the Sample Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Find the sample application in the **zephyr-ia/samples/intel/heci/host/** code base for Host (Zephyr IA).

2. Build the sample code using following build command

.. code:: c

   west build -p -b ehl_crb ../zephyr-ia/samples/intel/heci/host/


3. Find the sample application in the code base for PSE FW:

https://github.com/intel/pse-fw/tree/main/apps/samples/base_fw/heci

For more details on source code and build PSE FW heci sample app::
  
  west init -m https://github.com/intel/pse-fw
  west update
  cd ehl_pse-fw
  ./build.sh apps/samples/base_fw/heci/

4. Please refer PSE SDK user guide for obtain source code, build and flash PSE FW.

Please refer `Zephyr documentation <https://docs.zephyrproject.org/2.6.0/boards/x86/ehl_crb/doc/index.html>`_ for details on loading Zephyr with BIOS.

Please refer `SBL Native Boot setup <slim_bootloader.rst>`_  for details on loading Zephyr with Slim Bootloader.

Expected Output
~~~~~~~~~~~~~~~

::

  user_app_init
  test app ++++++++++++++++++++++++++++++
  enter
  smpl new heci event 1
  new conn: 0
  HECI cmd will send in 1 seconds
  HECI cmd will send in 2 seconds
  Send get SMPL_GET_VERSION command
  smpl new heci event 1
  smpl cmd =  1
  SMPL_GET_VERSION 0 1 2 3
  HECI cmd will send in 1 seconds
  HECI cmd will send in 2 seconds
  Send get SMPL_GET_VERSION command
  smpl new heci event 1
  smpl cmd =  1
