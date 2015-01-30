#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"

int main(int argc, char * argv[])
{
	char name[32];
	int index = 0;
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	
	printf("Please enter color name (in lower case) (e.g. 'black'): ");
	scanf("%30s",name);
	
	printf("Test: '%s'\n",name);
	
	index = get_color_index(name);
	
	printf("Index: '%d'\n",index);
	
	r = get_red(index);
	g = get_grn(index);
	b = get_blu(index);
	
	printf("R G B: 0x%02x 0x%02x 0x%02x \n",r,g,b);
	
	r = get_red_from_name(name);
	g = get_grn_from_name(name);
	b = get_blu_from_name(name);
	
	printf("R G B: 0x%02x 0x%02x 0x%02x \n",r,g,b);

	exit(0);
}
