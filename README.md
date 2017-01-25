# /!\ WARNING /!\ TOP SECRET
# M51 Missile Embedded System
## For ARMADEUS APF28-Dev 

---------------------------------------
## Content:
---------------------------------------

- client.c and server.c : the client-server code, to send the text to translate in morse to the APF28-Dev. (client.c must be cross-compiled on the card)

- crypto.c: contains 2 functions, encrypt and decrypt (Ceasar encryption, +3).To be cross-compiled on the card.

- fct_led.c :this file contains the functions to translate the alphabetic message in morse code. The returned value is a 1 or a 0, making the  flashing light on or off, with different times os sleep to distinct words

- params.h : contains the informations of the GPIO connected with the LED, with the file value, inside which one the value 1 or 0 is imported.



---------------------------------------
## Installation:
---------------------------------------

1)

2)

3)



----------------------------------------
## Other:
----------------------------------------

For any question, feel free to contact us!
