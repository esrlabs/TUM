/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains IntervalFilter class.
 * @file		IntervalFilter.h
 * @ingroup		filter
 */
#ifndef _INTERVALFILTER_H_
#define _INTERVALFILTER_H_

#include "commonTypes.h"
#include "can/canframes/CANFrame.h"
#include "can/filter/IFilter.h"
#include "can/filter/IMerger.h"
#include "util/Uncopyable.h"

namespace can
{

/**
 * Cpp2CAN IntervalFilter
 * @author		gerd.schaefer, matthias.kessler
 *
 * @see	IFilter
 */
class IntervalFilter :
	public IFilter
{
public:
	/** maximum id the filter may take */
	static const uint16	MAX_ID	= CANFrame::MAX_FRAME_ID;

	/**
	 * constructor
	 * @post	getLowerBound() == MAX_ID
	 * @post	getUpperBound() == 0x0
	 *
	 * Nothing wil be accepted by default
	 */
	IntervalFilter();

	/**
	 * constructor initializing an interval
	 * @param	from	first id that will be accepted
	 * @param	to		last id that will be accepted
	 * @pre		from <= MAX_ID
	 * @pre		to <= MAX_ID
	 * @post	getLowerBound() == from
	 * @post	getUpperBound() == to
	 *
	 * @note
	 * If from or to exceed MAX_ID, they will be set to MAX_ID.
	 */
	explicit IntervalFilter(uint16 from, uint16 to);

	/**
	 * @see		IFilter::add()
	 * @param	id	id to add to filter
	 * @pre		id <= MAX_ID, otherwise no effect
	 * @post	getLowerBound() == min(id, getLowerBound())
	 * @post	getUpperBound() == max(id, getUpperBound())
	 *
	 * @note
	 * This call is equal to add(id, id).
	 */
	virtual void add(uint16 id)
	{
		if (id <= MAX_ID)
		{
			add(id, id);
		}
	}

	/**
	 * @see		IFilter::add()
	 * @param	from	lower bound of interval to add
	 * @param	to		upper bound of interval to add
	 * @pre		from <= MAX_ID
	 * @pre		to <= MAX_ID
	 * @post	getLowerBound() == min(from, getLowerBound())
	 * @post	getUpperBound() == max(to, getUpperBound())
	 *
	 * If from or to exceed MAX_ID, they will be set to MAX_ID.
	 *
	 * This call will not replace the current filter configuration, but
	 * adjust lower and upper bound of the filter according to the parameters.
	 */
	virtual void add(uint16 from, uint16 to);

	/**
	 * checks if an id matches the filter
	 * @param	id		id to check
	 * @return
	 * 			- true: filter matches id
	 * 			- false: id is not in filters range
	 */
	virtual bool match(uint16 id) const
	{
		return (id >= fFrom) && (id <= fTo);
	}

	/**
	 * @see		IFilter::acceptMerger()
	 */
	virtual void acceptMerger(IMerger& merger)
	{
		merger.mergeWithInterval(*this);
	}

	/**
	 * @see		IFilter::clear();
	 */
	virtual void clear();

	/**
	 * @see		IFilter::open();
	 */
	virtual void open();

	/**
	 * @return	lower bound of filter
	 */
	uint16 getLowerBound() const
	{
		return fFrom;
	}

	/**
	 * @return	upper bound of filter
	 */
	uint16 getUpperBound() const
	{
		return fTo;
	}
private:
	MAKE_UNCOPYABLE(IntervalFilter)
	//fields
	uint16 fFrom;
	uint16 fTo;
};

} /*namespace can*/

#endif //_INTERVALFILTER_H_
