#ifndef _PARSE_H
#define _PARSE_H

typedef struct{
	uint8_t eventId;
	uint8_t* Event;
}Event_TypeDef;

typedef enum{
	SUCCESS = 1,
	FAILURE = !SUCCESS;
}status;

status parseString(uint8_t* Input, Event_TypeDef* events){
	int count = 0;
	while(*Input != '\0')
	{	
		
		while(*Input != ',')
			Input++;
		do
		{
			*(events[0]->Event++) = *Input++;
		}while(*Input != ';');
		events[count]->eventId = count++;
	}
}




#endif