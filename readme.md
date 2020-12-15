#DTM Testing via Gatt

This is a code example that enables DTM test trigger via GATT.

Here is how it works:


This is works with any type of scanner application on a Smartphone. I like to use the Light Blue App from PunchThrough

There is a DTM Control Service.

The Transmit Power characteristic configures the Transmit Power value. Eg. For 10 dbm, use 0x64.

The PHY Type characteristic configures the Phy used on the test.
0x1 – 1M
0x2 – 2M
0x4 – S8
0x8 – S2

The modulation Scheme holds the transmit mode ( 0 – 8)

0 - PRBS9 (GFSK)
1- 11110000
2- 10101010
3- 11111111
4- 00000000
5- 00001111
6- 01010101
7- PN9 Continuously Modulated Output
8- Unmodulated carrier


The Packet size controls the Packet length.

Since we have no way to interrupt the test once started, I have created the Test Time Characteristic, which will hold in seconds, how much time the test will run.

The DTM ON characteristic triggers the test when “1” is written to it. Once the test is triggered the device will disconnect from the phone and will run until the pre-configured time set on the Test Time Characteristic expires.

Once the test is done, reconnect to the device and check the Results characteristic to retrieve the amount of packets that have been transmitted.


This was built for the EFR32MG21A010F1024IM32 and the Silicon Labs Bluetooth Stack 2.13.6.0

In order to compile this, please make sure you clone this to your Simplicity Studio workspace and that you have installed the right version of the Gecko SDK and Bluetooth Stack.

KBA showing how to import this to Simplicity Studio: https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2017/11/09/how_to_import_a_blue-Z1ix


*******************************************************************************
* # License
* <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
*******************************************************************************
*
* The licensor of this software is Silicon Laboratories Inc. Your use of this
* software is governed by the terms of Silicon Labs Master Software License
* Agreement (MSLA) available at
* www.silabs.com/about-us/legal/master-software-license-agreement. This
* software is distributed to you in Source Code format and is governed by the
* sections of the MSLA applicable to Source Code.
*
******************************************************************************/
