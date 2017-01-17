#include "params.h"

void encrypt(char *str)
{
	int n=0;
	char *p=str;

	while(*p)
	{
		str[n] = (*p + 3)%256;
		n++;
		p++;
	}
	str[n++]='\0';
}

void decrypt(char *str)
{
	int   n=0;
	char *p=str;

	while(*p)
	{
		str[n] = (*p - 3)%256;
		p++;
		n++; 
	}
	str[n++]='\0';
}

