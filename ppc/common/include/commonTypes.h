/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

/* standard types file to be used for
 * all C++ basic software components */

#ifdef UNIT_TEST

typedef unsigned char       		uint8;
typedef unsigned short        		uint16;
typedef unsigned int        		uint32;
typedef unsigned long long int      uint64;

typedef signed char       			sint8;
typedef signed short        		sint16;
typedef signed int        			sint32;
typedef signed long long int      	sint64;

#else
#include "Std_Types.h"

typedef volatile uint32           	vuint32;
typedef volatile uint32           	vuint32_t;
#endif

#endif /* COMMON_TYPES_H */
