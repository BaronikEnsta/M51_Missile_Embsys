#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "params.h"

void court(FILE *fichier) 
{	 	fprintf(fichier, "1"); // Écriture du message reçu
		usleep(250000);
		fprintf(fichier, "0"); // Écriture du message reçu
		usleep(500000);
}

void longt(FILE *fichier)
{
	 	fprintf(fichier, "1"); // Écriture du message reçu
		usleep(750000);
		fprintf(fichier, "0"); // Écriture du message reçu
		usleep(500000);
		
}

void att(FILE *fichier)
{
	         sleep(1);
}


void traduct (char* message, char* Alp, char** Tab, char* resultat)
{
	int i=0;
	int indice=0;
	resultat = strcat(resultat,"pp");

	for (i=0;i<strlen(message);i++){
		int j=0;
		while (j<strlen(Alp)){
			if (message[i]==Alp[j]){
				indice = j;
				break;
			} else {
				j++;
			}
		}

		resultat = strcat(resultat,Tab[indice]);
		
	}
	printf("%s\n",resultat);
}

void ecriture (char* resultat)
{
	int i=0;
	
	FILE *fichier = fopen(GPIO, "w");	
	for (i=0;i<strlen(resultat);i++){
		if (resultat[i]=='l'){
			longt(fichier);
		}	
		if (resultat[i]=='c'){
			court(fichier);
		}
		if (resultat[i]=='p'){
			att(fichier);
		}
	}	
	fclose(fichier);

}

void led(char* message)
{
char* Tab[] = {"cl","lccc","lclc","lcc","c","cclc","llc","cccc","cc","clll","lcl","clcc","ll","lc","lll","cllc","llcl","clc","ccc","l","ccl","cccl","cll","lccl","lcll","llcc","cllll","cclll","cccll","ccccl","ccccc","lcccc","llccc","lllcc","llllc","lllll","p"};
char Alp[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',' '};
char resultat[20];
bzero(resultat, 20);

traduct(message, Alp, Tab, resultat);
ecriture (resultat);

}




