.. _tgpio:

TGPIO
#####

Overview
********
Timed GPIO sample application performs tests for adjusting the rate and offset
for timers supported by TGPIO. The application also tests various operating
modes of TGPIO like time based input, event ceiling based input and repeated
output. Test for checking which pins are available as TGPIO pins is also
a part of the application.

Building and Running
********************
Standard build and run procedure defined for intel_pse target to be
followed.
For unlimited output and event ceiling input testing, loopback pins 27 and 28.
For unlimited output and timebased input testing and rate adjustment testing, loopback pins 27 and 28.

Sample Output
*************
Bind success [TGPIO_0]

Test for time adjustment
-------------------------
[TGPIO_0] Timer: 0, Time Now: 100:860, Adding 99999896 nsecs
[TGPIO_0] Timer: 0, Adjust Done, Added 99999896 nsecs, Time Now: 100:606040106

Test for rate adjustment
-------------------------
[TGPIO_0] Pin: 28, Timer: 1, Scheduled at:00000101:00000000
[cb-TGPIO_0] adj_freq: [pin -27][ts -101: 99974735][ec - 2], running slow with 2000 nsecs
[TGPIO_0] Adjusting TMT_0 frequency
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:199974451][ec - 3], running slow with 284 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:299974451][ec - 4], running fast with 0 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:399974450][ec - 5], running slow with 1 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:499974450][ec - 6], running fast with 0 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:599974449][ec - 7], running slow with 1 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:699974449][ec - 8], running fast with 0 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:799974448][ec - 9], running slow with 1 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:899974448][ec - 10], running fast with 0 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -101:999974447][ec - 11], running slow with 1 nsecs
[cb-TGPIO_0] adj_freq: [pin -27][ts -102: 99974452][ec - 12], running fast with 5 nsecs

Test for cross timestamp
-------------------------
[TGPIO_0] Timer: 0, Local Time: 00000102:120742912, Ref. Time: 00000018:91121351

Test for unlimited output and timebased input
-----------------------------------------------
[TGPIO_0] Pin: 28, Timer: 0, Scheduled at:00000101:09544580
[TGPIO_0] Pin: 27, Timer: 0, Scheduled at:00000101:15488345

Test for unlimited output and event ceiling input
---------------------------------------------------
[TGPIO_0] Pin: 28, Timer: 0, Scheduled at:00000101:31757245
[TGPIO_0] Pin: 27, Timer: 0, Scheduled at:00000101:31757245

[cb-TGPIO_0][pin -27][ts -101: 40757285][ec -10]
[cb-TGPIO_0][pin -27][ts -101: 50757285][ec -20]
[cb-TGPIO_0][pin -27][ts -101: 60757285][ec -30]
[cb-TGPIO_0][pin -27][ts -101: 70757285][ec -40]
[cb-TGPIO_0][pin -27][ts -101: 85757285][ec -55]
[cb-TGPIO_0][pin -27][ts -101: 95757285][ec -65]
[cb-TGPIO_0][pin -27][ts -101:105757285][ec -75]
[cb-TGPIO_0][pin -27][ts -101:115757285][ec -85]
[cb-TGPIO_0][pin -27][ts -101:125757285][ec -95]
[cb-TGPIO_0][pin -27][ts -101:140757285][ec -110]
[cb-TGPIO_0][pin -27][ts -101:150757285][ec -120]
[cb-TGPIO_0][pin -27][ts -101:160757285][ec -130]
[cb-TGPIO_0][pin -27][ts -101:170757285][ec -140]
[cb-TGPIO_0][pin -27][ts -101:180757285][ec -150]
[cb-TGPIO_0][pin -27][ts -101:195757285][ec -165]

.. code-block:: console
