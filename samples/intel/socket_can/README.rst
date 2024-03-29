.. _socket-can-sample:

Socket CAN
##########

Overview
********

The socket CAN sample is a server/client application that sends and receives
raw CAN frames using BSD socket API.

The application consists of these functions:

* Setup function which creates a CAN socket, binds it to a CAN network
  interface, and then installs a CAN filter to the socket so that the
  application can receive CAN frames.
* Receive function which starts to listen the CAN socket and prints
  information about the CAN frames.
* Send function which starts to send raw CAN frames to the bus.

The source code for this sample application can be found at:
:zephyr_file:`samples/net/sockets/can`.


