/*************************************************************************
 * conn_map.h - Header file to define connector and pin mappings for gpio
 * pins on the BeagleBoneBlack. This file is part of sysfs.c, a simple c 
 * library to implement gpio pin control using sysfs from userspace on 
 * the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/

#ifndef __CONN_MAP_H__
#define __CONN_MAP_H__

#ifdef  __cplusplus
extern "C" {
#endif

static const int conn_map[] = { 
	0,0,9,9,9,9,0,9,8,8,8,8,0,0,9,9,
	0,0,0,0,9,0,8,8,0,0,8,8,0,0,9,9,
	8,8,8,8,8,8,8,8,0,0,0,0,8,8,8,8,
	9,9,9,9,0,0,0,0,0,0,0,0,9,8,8,8,
	0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,0,0,0,0,8,8,8,8,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,
	9,9,0,9,0,9 };
	
static const int pin_map[] = { 
	0,0,22,21,18,17,0,42,35,33,31,32,0,0,26,24,
	0,0,0,0,41,0,19,13,0,0,14,17,0,0,11,13,
	25,24,5,6,23,22,3,4,0,0,0,0,12,11,16,15,
	15,23,14,16,0,0,0,0,0,0,0,0,12,26,21,20,
	0,18,7,8,10,9,45,46,43,44,41,42,39,40,37,38,
	36,34,0,0,0,0,27,29,28,30,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,29,
	30,28,0,27,0,25 };

#endif	// __CONN_MAP_H__
