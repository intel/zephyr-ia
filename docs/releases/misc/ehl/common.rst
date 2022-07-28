Developer prerequisites
-----------------------

* Developer should be familiar with Zephyr RTOS. `Please refer Zephyr documentation if new to Zephyr. <https://docs.zephyrproject.org/2.7.0/introduction/index.html>`_

* Following additional documents you may need to refer before start on IA Zephyr project for Elkhart Lake:

`Intel Atom® x6000E Series, and Intel® Pentium® and Celeron® N and J Series Processors for Internet of Things (IoT) Applications, External Design Specification (EDS), Volume 2 (Book 2 of 4), Mule Creek Canyon <https://cdrdv2.intel.com/v1/dl/getContent/614109?explicitVersion=true>`_

`Intel Atom® x6000E Series, and Intel® Pentium® and Celeron® N and J Series Processors for Internet of Things (IoT) Applications, External Design Specification (EDS), Volume 2 (Book 3 of 4), Intel® Programmable Services Engine (Intel® PSE) <https://cdrdv2.intel.com/v1/dl/getContent/614110?explicitVersion=true>`_

`Intel Atom® x6000E Series, and Intel® Pentium® and Celeron® N and J Series Processors for Internet of Things (IoT) Applications, External Design Specification (EDS), Volume 1 <https://cdrdv2.intel.com/v1/dl/getContent/601458?explicitVersion=true>`_

Most of the links provided in this release notes require `Intel® Premier Support Access <https://www.intel.in/content/www/in/en/design/support/ips/training/access-and-login.html>`_
and user expected to have access to the Resource & Design Center (RDC) before going through the release notes.

Development system prerequisites
--------------------------------

User should be familiar with:

* Zephyr RTOS. `Please refer Zephyr documentation if new to Zephyr. <https://docs.zephyrproject.org/2.7.0/introduction/index.html>`_

* Elkhart Lake CRB and how to setup board and flash IFWI. 

Following additional documents you may need to refer before start on IA Zephyr project for Elkhart Lake:

`Elkhart Lake - Customer Reference Board (CRB) - Getting Started Guide <https://cdrdv2.intel.com/v1/dl/getContent/615860?explicitVersion=true>`_

`Elkhart Lake- Intel® Programmable Services Engine SDK Add-in Card User Guide <https://cdrdv2.intel.com/v1/dl/getContent/632302?explicitVersion=true>`_

`Intel® Programmable Services Engine SDK Get Started Guide (If enable HECI stack) <https://cdrdv2.intel.com/v1/dl/getContent/608527?explicitVersion=true>`_

General Informations
--------------------

For enable or configure a driver instance, please update following DTS overlay files:

::

    zephyr-ia/overlay/ehl_crb.overlay

`Please refer Zephyr documentation for more details on Devicetree. <https://docs.zephyrproject.org/2.7.0/guides/dts/index.html>`_
