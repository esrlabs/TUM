/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains basic type traits.
 * \file	SBaseTypes.h
 * \ingroup	sstl
 */
#ifndef SBASETYPES_H_
#define SBASETYPES_H_

/**
 * type traits
 * \param	T	type to get traits from
 *
 * This class may be used to save some type work.
 */
template<typename T>
struct STypeTraits
{
	/** unsigned integral type */
	typedef unsigned int	size_type;
	/** signed integral type */
	typedef signed int		difference_type;
	/** type of T itsself */
	typedef T				value_type;
	/** pointer to T */
	typedef T*				pointer;
	/** reference to T */
	typedef T&				reference;
	/** const reference to T */
	typedef const T&		const_reference;
};

#endif /*SBASETYPES_H_*/
