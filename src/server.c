#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include "crypto.c"
#include "params.h"
#include "fct_led.c"

void cleaning(int socket_desc)
{
	/*clean the mess*/
	printf("Closing socket and exiting...\n");
	close(socket_desc);
	exit(0);
}

int main(int argc , char *argv[])
{
	
		int socket_desc , client_sock , c , read_size;
		struct sockaddr_in server , client;
		char client_message[MAXSIZE];
	
		//gentle interrupt
		if(signal( SIGINT, cleaning) == SIG_ERR){
    		printf ("Unable to install handler\n");
    		return 1;
  		}

		//Create socket
		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc == -1){
			printf("Could not create socket");
			return 1;
		}
		puts("Socket created");
	
		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORT_serv);
			
		//Bind
		if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
			//print the error message
			perror("Bind failed. Error");
			return 1;
		}
		puts("bind done");
	

	while(1) {
		//Listen
		listen(socket_desc , 3);
	
		//Accept and incoming connection
		puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);
	
		//accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0){
			perror("accept failed");
			return 1;
		} puts("Connection accepted");
		bzero(client_message, MAXSIZE);
		//Receive a message from client
		while( (read_size = recv(client_sock , client_message, MAXSIZE , 0)) > 0 ){
			
			//decrypt and convert to morse code
			decrypt(client_message);
			led(client_message);
			
			//Send the message back to client
			write(client_sock , client_message, strlen(client_message));
			bzero(client_message, MAXSIZE);
		}
	
		if(read_size == 0){
			puts("Client disconnected");
			fflush(stdout);
		} else if(read_size == -1) {
			perror("recv failed");
		}
	}

	close(socket_desc);
	return 0;
}
