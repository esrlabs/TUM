/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains base types for iterators.
 * \file	SIteratorBaseTypes.h
 * \ingroup	sstl
 */
#ifndef SITERATORBASETYPES_H_
#define SITERATORBASETYPES_H_

/**
 * input iterator
 *
 * \section	Description
 * May advance through a iterator range. Reads each
 * value exactly one time.
 */
struct SInputIteratorTag {};

/**
 * output iterator
 *
 * \section	Description
 * May advance through a iterator range and alter values.
 */
struct SOutputIteratorTag {};

/**
 * forward iterator
 *
 * \section	Description
 * May advance through a iterator range and read each value
 * more than on time.
 */
struct SForwardIteratorTag : public SInputIteratorTag {};

/**
 * bidirectional iterator
 *
 * \section	Description
 * May go through a iterator range in both directions and
 * read each value more than one time
 */
struct SBidirectionalIteratorTag : public SForwardIteratorTag {};

/**
 * random access iterator
 *
 * \section	Description
 * May go through a iterator range like a pointer through an
 * array and read each value more than one time.
 */
struct SRandomAccessIteratorTag : public SBidirectionalIteratorTag {};

/**
 * optional base class for iterators
 * \param	Category	iterators category
 * \param	T			type iterator points to
 * \param	Distance	signed integral type
 * \param	Pointer		pointer to T
 * \param	Reference	reference to T
 *
 * Classes may subclass this class to save some typedef work.
 */
template<
	typename Category,
	typename T,
	typename Distance = signed int,
	typename Pointer = T*,
	typename Reference = T&>
struct SIterator
{
	/** the iterators category */
	typedef Category	iterator_category;
	/** type of value iterator points to */
	typedef T			value_type;
	/** signed integral type */
	typedef Distance	difference_type;
	/** pointer to value type */
	typedef Pointer		pointer;
	/** reference to value type */
	typedef Reference	reference;
};

/**
 * traits for iterators
 * \param	Iterator	iterator to generate traits for
 */
template<typename Iterator>
struct SIteratorTraits
{
	/** the iterators category */
	typedef typename Iterator::iterator_category	iterator_category;
	/** type of value iterator points to */
	typedef typename Iterator::value_type			value_type;
	/** signed integral type */
	typedef typename Iterator::difference_type		difference_type;
	/** pointer to value */
	typedef typename Iterator::pointer				pointer;
	/** reference to value */
	typedef typename Iterator::reference			reference;
};

/**
 * special implementation for pointers
 * \param	T	type of value for whose pointer traits are generated
 *
 * \see		SIteratorTraits
 */
template<typename T>
struct SIteratorTraits<T*>
{
	typedef SRandomAccessIteratorTag 	iterator_category;
	typedef T							value_type;
	typedef signed int					difference_type;
	typedef value_type*					pointer;
	typedef value_type&					reference;
};

/**
 * special implementation for const pointers
 * \param	T	type of value for whose const pointer traits are generated
 *
 * \see		SIteratorTraits
 *
 */
template<typename T>
struct SIteratorTraits<const T*>
{
	typedef SRandomAccessIteratorTag 	iterator_category;
	typedef T							value_type;
	typedef signed int					difference_type;
	typedef const value_type*			pointer;
	typedef const value_type&			reference;
};

#endif /*SITERATORBASETYPES_H_*/
