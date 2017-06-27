/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains STL like algorithms.
 * \file	SAlgorithm.h
 * \ingroup	sstl
 */
#ifndef SALGORITHM_H_
#define SALGORITHM_H_

#include "SIteratorBaseTypes.h"

/**
 * returns minimum of two values
 * \param	T	type of values
 * \param	t1	first value
 * \param	t2	second value
 * \return	minimum of t1 and t2
 */
template<typename T>
inline const T& smin(const T& t1, const T& t2)
{
	return (t1 < t2 ? t1 : t2);
}

/**
 * returns maximum of two values
 * \param	T	type of values
 * \param	t1	first value
 * \param	t2	second value
 * \return	maximum of t1 and t2
 */
template<typename T>
inline const T& smax(const T& t1, const T& t2)
{
	return (t1 > t2 ? t1 : t2);
}

/**
 * swaps two values
 * \param	T	type of values
 * \param	t1	first value
 * \param	t2	second value
 */
template<typename T>
inline void sswap(T& t1, T& t2)
{
	T t = t1;
	t1 = t2;
	t2 = t;
}

/**
 * finds a value in a given iterator range
 * \param	InputIterator		type of iterators
 * \param	EqualityCompareable	type of value to find
 * \param	first	begin of range
 * \param	last	and of range
 * \param	value	value to find in range
 * \return	iterator to first element equal to value in range
 */
template<
	typename InputIterator,
	typename EqualityCompareable>
inline InputIterator sfind(
	InputIterator first,
	InputIterator last,
	const EqualityCompareable& value)
{
	return sfind(
		first,
		last,
		value,
		typename SIteratorTraits<InputIterator>::iterator_category());
}

/**
 * implementation of sfind for input iterators
 * \see		sfind()
 */
template<
	typename InputIterator,
	typename EqualityCompareable>
inline InputIterator sfind(
	InputIterator first,
	InputIterator last,
	const EqualityCompareable& value,
	SInputIteratorTag)
{
	while (!(first == last) && !(*first == value))
	{
		++first;
	}
	return first;
}

/**
 * removes all elements equal to a value from a range and copies it to another
 * \param	InputIterator		type of input range iterators
 * \param	OutputIterator		type of result range iterator
 * \param	EqualityCompareable	type of value to remove from input range
 * \param	first	begin of input range
 * \param	last	end of input range
 * \param	result	begin iterator of result range
 * \param	value	value to remove
 * \return	end of result range
 */
template<
	typename InputIterator,
	typename OutputIterator,
	typename EqualityCompareable>
inline OutputIterator sremove_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	const EqualityCompareable& value)
{
	while (first != last)
	{
		if (!(*first == value))
		{
			*result = *first;
			++result;
		}
		++first;
	}
	return result;
}

/**
 * removes all elements of a given value from a range
 * \param	ForwardIterator		type of range iterator
 * \param	EqualityCompareable	type of value to remove
 * \param	first	begin of range
 * \param	last	end of range
 * \param	value	value to remove from range
 * \return	iterator to result range
 */
template<
	typename ForwardIterator,
	typename EqualityCompareable>
ForwardIterator sremove(
	ForwardIterator first,
	ForwardIterator last,
	const EqualityCompareable& value)
{
  first = sfind(first, last, value);
  ForwardIterator i = first;
  return first == last ? first : sremove_copy(++i, last, first, value);
}

template<
	typename InputIterator,
	typename EqualityComparable>
typename SIteratorTraits<InputIterator>::difference_type scount(
	InputIterator first, InputIterator last,
	const EqualityComparable& value)
{
	typename SIteratorTraits<InputIterator>::difference_type result = 0;
	while (first != last)
	{
		if (*first == value)
		{
			++result;
		}
		++first;
	}
	return result;
}

#endif /*SALGORITHM_H_*/
