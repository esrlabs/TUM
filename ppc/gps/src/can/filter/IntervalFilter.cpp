/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#include "can/filter/IntervalFilter.h"
#include "util/SAlgorithm.h"

namespace can
{

#ifdef __GNUC__
const uint16 IntervalFilter::MAX_ID;
#endif

IntervalFilter::IntervalFilter()
{
	clear();
}

IntervalFilter::IntervalFilter(uint16 from, uint16 to) :
	fFrom(from),
	fTo(to)
{
	if (from > MAX_ID)
	{
		fFrom = MAX_ID;
	}
	if (to > MAX_ID)
	{
		fTo = MAX_ID;
	}
}

void IntervalFilter::add(uint16 from, uint16 to)
{
	if (from > MAX_ID)
	{
		from = MAX_ID;
	}
	if (to > MAX_ID)
	{
		to = MAX_ID;
	}
	//assert order
	if (from > to)
	{
		sswap(from, to);
	}
	//adjust lower bound
	fFrom = smin(fFrom, from);
	//adjust upper bound
	fTo = smax(fTo, to);
}

void IntervalFilter::clear()
{
	fFrom 	= MAX_ID;
	fTo		= 0;
}

void IntervalFilter::open()
{
	fFrom 	= 0x0;
	fTo		= MAX_ID;
}

} /*namespace can*/
