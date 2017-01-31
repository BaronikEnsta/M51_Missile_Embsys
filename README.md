# /!\ WARNING /!\ TOP SECRET
# M51 Missile Embedded System
## For ARMADEUS APF28-Dev 

---------------------------------------
## Summary:
---------------------------------------

Simple client/server architecture for a APF28-Dev embedded card connected to a network.

The client take an input, "encrypt" it with a caesar cipher and send it to the server.

The server (on the card) decrypt the message and make a LED blink according to the morse code. It sends back an "ack" to the client. Upon client disconnection the server clears the socket and stays up.

By default, the LED has to be connected to the GPIO pin #18.

---------------------------------------
## Content:
---------------------------------------

### /src :

- client.c and server.c : the client-server code, to send the text to translate in morse to the APF28-Dev. (server.c must be cross-compiled on the card)

- crypto.c: contains 2 functions, encrypt and decrypt (Ceasar encryption, +3).To be cross-compiled on the card.

- fct_led.c :this file contains the functions to translate the alphabetic message in morse code. The returned value is a 1 or a 0, making the  flashing light on or off, with different times os sleep to distinct words

- params.h : Parameters header.
	- MAXSIZE : Maximum size in bytes for the message
	- IP_serv : Default IP for the server
	- PORT_serv : Default port for the socket
	- GPIO_value : Path to the file controlling the LED.
		(In order to test the program locally, you can change it to whatever is desired)

### /cross-compiler

Cross compiler binary for the APF28-Dev card.

### /scripts

SP99app : Shell script executed upon boot. It initializes the LED GPIO file and start the server.

---------------------------------------
## Installation:
---------------------------------------

1) Compilation of the sources:
	$ make

2) Cross compilation of the sources:
	$ make arm

3) Scp bin/server-arm on the card, in the /root directory
	(You can also scp bin/client-arm to do a local test on the card)

4) Scp scripts/S99app on the card, in the /etc/init.d directory

5) Reboot the card. If the everything goes well the LED will lit up for five seconds.

---------------------------------------
## Local test:
---------------------------------------

1) Change the value of GPIO_value inside params.h
	(e.g "./test.txt")
2) In the terminal :
	$ bin/server
   In another terminal :
	$ bin/client

3) Send message from the client and cat the content of test.txt to see if it changes


---------------------------------------
## Local test on the card:
---------------------------------------

1) In a ssh terminal :
	$ ./server-arm
In another :
	$ ./client-arm	

2) Send message, see if the LED blink


---------------------------------------
## Usage 
---------------------------------------

 (Assuming the installation process has been followed and the card is properly set up)

1) On the host :
	$ bin/client [serv_IP]

( 'serv_IP' being the ipV4 adress of the card on the local network )

2) Send message, see if the LED blink

---------------------------------------
## Example (Local)
---------------------------------------

$ make
gcc ./src/client.c -o ./bin/client
gcc ./src/server.c -o ./bin/server

$ bin/server
Socket created
bind done
Waiting for incoming connections...


$ bin/client
Socket created
Connected

Enter message : hello world 
Sending : khoor#zruog
Server reply :
ACK


	(on the server screen :)
	ppcccccclccclccllllllclllllclcclccclcc

$ cat test.txt 
1
$ cat test.xt 
0
$ cat test.xt 
1

	...etc.

### Upon client-side Ctrl+C :
	
Client-side :
	
	Closing socket and exiting...

Server-side :
	
	Client disconnected
	Waiting for incoming connections...
	
----------------------------------------
## Other:
----------------------------------------

For any question, feel free to contact us!
