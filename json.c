#include <stdio.h>
#include "parse.h"
#include <stdlib.h>

int main(){
	Event_TypeDef json[5];
	//Event_TypeDef *ptr = &json;
	char* string = "{\"id\":\"1614\",\"hash\":\"1e1a5ec62f79899d0892e81aa24441adaf2be276\",\"siddhartha\":\"Name\"}";
	parseString(string, json);
	printf("%s\n",json[0].Event);
	printf("%s\n",json[1].Event);
system("pause");
}