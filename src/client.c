#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#include "crypto.c"
#include "params.h" 

void cleaning(int socket_desc)
{
    /*clean the mess*/
    printf("Closing socket and exiting...\n");
    close(socket_desc);
    exit(0);
}

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[MAXSIZE] , server_reply[MAXSIZE];
     
    //Gentle interrupt 
    if(signal( SIGINT, cleaning) == SIG_ERR){
        printf ("Unable to install handler\n");
        return 1;
    }

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("Could not create socket");
    }
    puts("Socket created");
    
    if (argc == 1) {
	   server.sin_addr.s_addr = inet_addr(IP_serv);
    } else {
	   server.sin_addr.s_addr = inet_addr(argv[1]);
    }

    server.sin_addr.s_addr = inet_addr(IP_serv);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_serv);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1){
        bzero(message, MAXSIZE);
        printf("Enter message : ");
        fgets(message, MAXSIZE, stdin);

        if(strlen(message)>=MAXSIZE){
            printf("Message is too big ! (MAXSIZE is %d)\n", MAXSIZE);
        } else {
            //Send some data
            encrypt(message);
            printf("Sending : %s\n", message);
            if(send(sock , message, strlen(message) , 0) < 0){
                puts("Send failed");
                return 1;
            }

            //Receive a reply from the server
            bzero(server_reply, MAXSIZE);
            if( recv(sock , server_reply, MAXSIZE , 0) < 0){
                puts("recv failed");
                break;
            }

            //decrypt(server_reply);
            puts("Server reply :");
            puts(server_reply);
            fflush(stdout);
        }
    }
     
    close(sock);
    return 0;
}
