/*************************************************************************
 * colors.h - A small module to help manipulate and lookup RGB color
 * values from color_defs.h
 * 
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/

#ifndef __COLORS_H__
#define __COLORS_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define ERROR -1
#define ERROR_OK 0

int get_num_colors(void);
int get_color_index(char * name);
int get_red_from_name(char * name);
int get_grn_from_name(char * name);
int get_blu_from_name(char * name);
char* get_color_name(int index);

#endif	// __COLORS_H__
