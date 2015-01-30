#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "color_defs.h"

int get_color_index(char * name)
{
	int i;

	for(i=0;i<NUM_COLORS;i++) {
		if (strcmp(color_names[i],name) == 0)
			return(i);
	}
	
	return(ERROR);
}

int get_red_from_name(char * name)
{
	return(red[get_color_index(name)]);
}

int get_grn_from_name(char * name)
{
	return(grn[get_color_index(name)]);
}

int get_blu_from_name(char * name)
{
	return(blu[get_color_index(name)]);
}

int get_red(int index)
{
	return(red[index]);
}

int get_grn(int index)
{
	return(grn[index]);
}

int get_blu(int index)
{
	return(blu[index]);
}

char* get_color_name(int index)
{
	if (index < 0)
		return(NULL);
	else if (index > NUM_COLORS)
		return(NULL);
	else
		return(color_names[index]);
}
