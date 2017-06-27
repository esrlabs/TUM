/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains IMerger interface.
 * @file 		IMerger.h
 * @ingroup		filter
 */
#ifndef _IMERGER_H_
#define _IMERGER_H_

#include "util/Uncopyable.h"

namespace can
{

//forward declarations
class BitFieldFilter;
class AbstractStaticBitFieldFilter;
class IntervalFilter;

/**
 * interface for class that are able to merge with other filter classes
 * @class		IMerger
 * @author		gerd.schaefer
 *
 * @see			BitFieldFilter
 * @see			AbstractStaticBitFieldFilter
 * @see			IntervalFilter
 */
class IMerger
{
public:
	IMerger() {}

	/**
	 * merges with a BitFieldFilter
	 * @param	filter	BitFieldFilter to merge with
	 */
	virtual void mergeWithBitField(BitFieldFilter& filter) = 0;

	/**
	 * merges with a AbstractStaticBitFieldFilter
	 * @param	filter	AbstractStaticBitFieldFilter to merge with
	 */
	virtual void mergeWithStaticBitField(AbstractStaticBitFieldFilter& filter) = 0;

	/**
	 * merges with a IntervalFilter
	 * @param	filter	IntervalFilter to merge with
	 */
	virtual void mergeWithInterval(IntervalFilter& filter) = 0;
private:
	MAKE_UNCOPYABLE(IMerger)
};

} //namespace can

#endif //_IMERGER_H_
