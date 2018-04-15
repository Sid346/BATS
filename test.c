#include <stdio.h>
#include "parse.h"
#include <stdlib.h>

int main(){
	Event_TypeDef json[5];
	//Event_TypeDef *ptr = &json;
	char* string = "id:1,eve:Maths;id:2,eve:physics";
	parseString(string, json);
	printf("%s\n",json[0].Event);
	printf("%s\n",json[1].Event);
system("pause");
}