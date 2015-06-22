/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */
#ifndef BUSID_H_
#define BUSID_H_

#include "commonTypes.h"
#include "util/Uncopyable.h"

//forward declarations
class BusIdIterator;

/**
 * Abstraction for bus ids used throughout the system.
 * @author	matthias.kessler
 *
 * BusId contains constants for all busses used and provides an iterator
 * to access them. Each BusId will have an index that is unique in the system.
 */
class BusId
{
public:
	enum { MAX_INDEX = 4 };
	/** iterator over BusIds */
	typedef BusIdIterator	iterator;
	/** maximum number of busses, used to allocate static memory */
	static const uint8	MAX_NUMBER_OF_BUSSES 	= MAX_INDEX;
	static const uint8	NUMBER_OF_LIN_BUSSES 	= 1;

	static const BusId 	BODYCAN;
	static const BusId  LIN;
	static const BusId  TAS;
	static const BusId 	SELFDIAG;
	static const BusId 	INVALID;	//MUST be last BusId and is not part of MAX_NUMBER_OF_BUSSES

	/**
	 * constructor
	 * @param	name	string representation of BusId
	 */
	explicit BusId(const char* name);

 	/**
 	 * @return	the BusIds name
 	 */
	const char* getName() const
	{
		return fpName;
	}

	/**
	 * @return	the BusIds unique index
	 */
	uint8 toIndex() const
	{
		return fId;
	}

	uint8 toCANIndex() const;

	uint8 toLINIndex() const;

	/**
	 * @param	index	index of BusId to access
	 * @return	BusId at given index
	 */
	static const BusId& get(uint8 index);

	/**
	 * @return	iterator to first BusId
	 */
	static iterator begin();

	/**
	 * @return	iterator one past last BusId
	 */
	static iterator end();

	/**
	 * @return	total number of busses (excluding INVALID)
	 */
	static uint8 numberOfBusses()
	{
		return sfIdCount;
	}
private:
	MAKE_UNCOPYABLE(BusId)

	//friends
	friend bool operator==(const BusId& x, const BusId& y);
	friend bool operator!=(const BusId& x, const BusId& y);
	friend class BusIdIterator;
	//fields
	uint8		fId;
	const char* fpName;
	//static fields
	static uint8 	sfIdCount;
	static BusId*	sfBusId[MAX_NUMBER_OF_BUSSES];
};

/**
 * Compares two given BusIds
 * @param	x	first BusId to compare
 * @param	y	second BusId to compare
 * @return
 * 			- true	BusIds are equal
 * 			- false	BusIds are not equal
 */
inline bool operator==(const BusId& x, const BusId& y)
{
	return (x.fId == y.fId);
}

/**
 * Compares two given BusIds
 * @param	x	first BusId to compare
 * @param	y	second BusId to compare
 * @return
 * 			- true	BusIds are not equal
 * 			- false	BusIds are equal
 */
inline bool operator!=(const BusId& x, const BusId& y)
{
	return (x.fId != y.fId);
}

/**
 * Iterator for BusIds.
 * @author	matthias.kessler
 */
class BusIdIterator
{
public:
	/** pointer to a BusId */
	typedef BusId*	pointer;
	/** reference to a BusId */
	typedef BusId&	reference;

	/**
	 * constructor
	 * @param	pBusId	pointer to BusId this iterator points initially to
	 */
	explicit BusIdIterator(BusId* pBusId) :
		fpBusId(pBusId)
	{}

	/**
	 * copy constructor
	 * @param	itr		iterator to copy from
	 */
	BusIdIterator(const BusIdIterator& itr) :
		fpBusId(itr.fpBusId)
	{}

	/**
	 * assignment operator
	 * @param	itr		iterator to copy from
	 */
	BusIdIterator& operator=(const BusIdIterator& itr)
	{
		if (&itr != this)
		{
			fpBusId = itr.fpBusId;
		}
		return *this;
	}

	/**
	 * @return	pointer to BusId iterator currently points to
	 */
	pointer operator->() const
	{
		return fpBusId;
	}

	/**
	 * @return	reference to BusId iterator currently points to
	 */
	reference operator*() const
	{
		return *fpBusId;
	}

	/**
	 * prefix increment operator
	 * @return	next iterator
	 */
	BusIdIterator& operator++()
	{
		if (fpBusId->toIndex() < BusId::sfIdCount-2)//-2 because of INVALID is last BusId
		{
			fpBusId = BusId::sfBusId[fpBusId->toIndex() + 1];
		}
		else
		{
			fpBusId = 0L;
		}
		return *this;
	}

private:
	//friends
	friend bool operator==(const BusIdIterator& x, const BusIdIterator& y);
	friend bool operator!=(const BusIdIterator& x, const BusIdIterator& y);
	//fields
	BusId*	fpBusId;
};

/**
 * compares two BusIdIterators
 * @param	x	first BusIdIterators to compare
 * @param	y	second BusIdIterators to compare
 * @return
 * 			- true	BusIdIterators are equal
 * 			- false	BusIdIterators are not equal
 */
inline bool operator==(const BusIdIterator& x, const BusIdIterator& y)
{
	return (x.fpBusId == y.fpBusId);
}

/**
 * compares two BusIdIterators
 * @param	x	first BusIdIterators to compare
 * @param	y	second BusIdIterators to compare
 * @return
 * 			- true	BusIdIterators are not equal
 * 			- false	BusIdIterators are equal
 */
inline bool operator!=(const BusIdIterator& x, const BusIdIterator& y)
{
	return (x.fpBusId != y.fpBusId);
}

#endif /*BUSID_H_*/
