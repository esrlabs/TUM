/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * @file	BusIdMask.h
 */
#ifndef BUSIDMASK_H_
#define BUSIDMASK_H_

#include "util/Mask.h"
#include "busId/BusId.h"

typedef Mask<BusId, uint32>	BusIdMask;

#endif /*BUSIDMASK_H_*/
