#ifndef _PARSE_H
#define _PARSE_H

#include <stdio.h>

typedef struct{
	char eventId;
	char Event[100];
}Event_TypeDef;

typedef enum{
	SUCCESS = 1,
	FAILURE = !SUCCESS
}status;

void delay(){
	int counter = 0xFFFF;
	while(--counter!=0);
}

status parseString(char* Input, Event_TypeDef* events){
	int count = 0;
	int counter;
	while(*Input != '\0')
	{	
		while(*Input != ',')
			Input++;
		while(*Input != ':')
			Input++;
		Input++;
		events[count].eventId = count;
		counter = 0;
		while(*Input != ';')
		{
			events[count].Event[counter++] = *Input++;
			if(*Input == '\0' || *Input == ';' || *Input == ',')
			{	
				events[count].Event[counter++] = '\0';
				break;
			}
		}
		count++;


	}
}
#endif