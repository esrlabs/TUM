/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains IFilter interface.
 * @file 		IFilter.h
 * @ingroup		filter
 */
#ifndef IFILTER_H_
#define IFILTER_H_

#include "commonTypes.h"
#include "util/Uncopyable.h"

namespace can
{
//forward declaration
class IMerger;

/**
 * common interface for filter classes
 * @author	matthias.kessler
 */
class IFilter
{
public:
	IFilter() {};

	/**
	 * adds a single id to the filter
	 * @param	id	id to add
	 * @post	filter.match(id)
	 */
	virtual void add(uint16 id) = 0;

	/**
	 * adds a range of ids to the filter
	 * @param	from	begin of range
	 * @param	to		end of range
	 * @post	filter.match(from...to);
	 */
	virtual void add(uint16 from, uint16 to) = 0;

	/**
	 * checks if a given id matches the filter
	 * @return
	 * 			- true: id matches filter
	 * 			- false: id does not match filter
	 */
	virtual bool match(uint16 id) const = 0;

	/**
	 * clears the filter so that nothing matches
	 */
	virtual void clear() = 0;

	/**
	 * opens the filters full range
	 */
	virtual void open() = 0;

	/**
	 * merges filter with a given merger
	 * @param	merger	IMerger to merge filter to
	 *
	 * This is part of the visitor pattern that is used to
	 * merge different kinds of filters.
	 */
	virtual void acceptMerger(IMerger& merger) = 0;
private:
	MAKE_UNCOPYABLE(IFilter)
};

} //namespace can

#endif /*IFILTER_H_*/
