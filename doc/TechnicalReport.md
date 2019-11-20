# Technical report Peaky Blinders
We are building a smart home. We mainly want to control lights and shutters. The system will be autonomous, but also will be controlable with a remote control, and the vocal command on a phone (Google Assistant).

## Components list
* Hardware :
	* Rasberry Pi or arduino (we will choose later according to our needs)
	* Relay
	* Connection wires
 	* Bluetooth or wifi module use to connect arduino to phone app (useless with rasberry pi 4) 
	* Diode	
	* controller
 	* Electronic shutters already installed
	* Electronic range finder
	* Coordinator device for zigbee
	* End-device for zigbee
	* Zigbee routor
	* Connect ampoule
	*  SIM900 GSM GPRS module to send SMS 
	* Température sensor

## Software design

There will be some kind of centralization where every modules will comunicate with a main card. It will be either through wifi, or zigbee. The softwares will be divided in multiple parts. 
* Handle the vocal control commands and decide what to do
* Communicate with the different modules
* Handle the IR remote commands and decide what to do
* When a command from the main board is received, act on the output (ie: the relays)

## Hardware design

The modules will be connected to zigbee capable boards and to relays. They will be some kind of gateway between the main module and the remote modules. The shutters module will have also a distance sensor to detect the proper opening or closing of the shutters.
The main module will have all the mandatory cards connected to it (Zigbee, IR receiver, Wifi)

test
