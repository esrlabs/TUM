/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#ifndef SLINKEDLIST_H_
#define SLINKEDLIST_H_

#include "util/SBaseTypes.h"
#include "util/SIteratorBaseTypes.h"
#include "util/CompileTimeConstraints.h"
#include <cassert>

template<typename T>
class SLinkedListSetNode
{
public:

	typedef T value_type;
	SLinkedListSetNode() :
		fpNext(0L),
		fAddedToList(false)
	{}

	T* getNext() const
	{
		return fpNext;
	}

	void setNext(T* pNext)
	{
		fpNext = pNext;
	}

	void addToList()
	{
		assert(!fAddedToList);
		fAddedToList = true;
	}

	void removeFromList()
	{
		fAddedToList = false;
	}
private:
	SLinkedListSetNode(const SLinkedListSetNode&);
	SLinkedListSetNode& operator=(const SLinkedListSetNode&);

	T* fpNext;
	bool fAddedToList;
};

template<typename T>
class SLinkedListSetIterator;

template<typename T>
class SLinkedListSet
	:	common::Derived_from<T, SLinkedListSetNode<T> >
{
private:
	/** type of list itsself */
	typedef SLinkedListSet<T>							self_type;
public:
	/** type of values stored in vector */
	typedef typename STypeTraits<T>::value_type			value_type;
	/** pointer to value */
	typedef typename STypeTraits<T>::pointer			pointer;
	/** reference to value */
	typedef typename STypeTraits<T>::reference			reference;
	/** const reference to value */
	typedef typename STypeTraits<T>::const_reference	const_reference;
	/** unsigned integral type */
	typedef typename STypeTraits<T>::size_type			size_type;
	/** signed integral type */
	typedef typename STypeTraits<T>::difference_type	difference_type;
	/** iterator type */
	typedef SLinkedListSetIterator<T>					iterator;
	/** const iterator type */
	typedef SLinkedListSetIterator<const T>				const_iterator;

	SLinkedListSet() :
		fpFirst(0L),
		fpLast(0L)
	{
		clear();
	}

	/**
	 * @note
	 * O(n)!
	 * @todo
	 * Maybe a field would be better
	 */
	size_type size() const
	{
		size_type size = (fpFirst) ? 1 : 0;
		for (const T* pNode = fpFirst; pNode != fpLast; pNode = pNode->getNext())
		{
			++size;
		}
		return size;
	}

	bool empty() const
	{
		return (fpFirst == 0L);
	}

	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
		fpFirst = 0L;
		fpLast = 0L;
	}

	const_reference front() const
	{
		assert(fpFirst);
		return *fpFirst;
	}

	reference front()
	{
		return const_cast<reference>(
				static_cast<const self_type&>(
					*this).front());
	}

	const_reference back() const
	{
		assert(fpLast);
		return *fpLast;
	}

	reference back()
	{
		return const_cast<reference>(
				static_cast<const self_type&>(
					*this).back());
	}

	void push_front(T& node)
	{
		if (contains_node(&node))
		{
			return;
		}
		node.addToList();
		node.setNext(fpFirst);
		fpFirst = &node;
		if (!fpLast)
		{//inserted first node
			fpLast = fpFirst;
			fpFirst->setNext(0L);
		}
	}

	void push_back(T& node)
	{
		if (empty())
		{//inserted first node
			fpFirst = &node;
		}
		else
		{
			if (contains_node(&node))
			{
				return;
			}
			fpLast->setNext(&node);
		}
		node.addToList();
		fpLast = &node;
		fpLast->setNext(0L);
	}

	void pop_front()
	{
		if (!fpFirst)
		{
			return;
		}
		fpFirst->removeFromList();
		fpFirst = fpFirst->getNext();
		if (!fpFirst)
		{//removed last element
			fpLast = 0L;
		}
	}

	void pop_back();

	iterator begin()
	{
		return iterator(fpFirst);
	}

	const_iterator begin() const
	{
		return const_iterator(fpFirst);
	}

	iterator end()
	{
		return iterator(0L);
	}

	const_iterator end() const
	{
		return const_iterator(0L);
	}

	iterator erase(iterator pos);

	iterator insert(iterator pos, T& value);

	void remove(const T& value);

	bool contains(const T& value) const
	{
		return contains_node(&value);
	}
private:
	SLinkedListSet(const SLinkedListSet&);
	SLinkedListSet& operator=(const SLinkedListSet&);

	T* findPredecessor(const T* pNode) const
	{
		T* pResult = fpFirst;
		while ((pResult != 0L) && (pResult->getNext() != pNode))
		{
			pResult = pResult->getNext();
		}
		return pResult;
	}

	bool contains_node(const T* pNodeToFind) const;

	T*	fpFirst;
	T*	fpLast;
};

template<typename T>
bool SLinkedListSet<T>::contains_node(const T* pNodeToFind) const
{
	T* pNode = fpFirst;
	while (pNode != 0L)
	{
		if (pNodeToFind == pNode)
		{
			return true;
		}
		pNode = pNode->getNext();
	}
	return false;
}

template<typename T>
void SLinkedListSet<T>::pop_back()
{
	if (!fpLast)
	{
		return;
	}
	fpLast->removeFromList();
	if (fpFirst == fpLast)
	{
		clear();
	}
	else
	{
		fpLast = findPredecessor(fpLast);
		assert(fpLast);
		fpLast->setNext(0L);
	}
}

template<typename T>
typename SLinkedListSet<T>::iterator SLinkedListSet<T>::erase(
	SLinkedListSet<T>::iterator pos)
{
	if (!fpFirst)
	{
		return end();
	}
	iterator next = pos;
	++next;
	if (pos == begin())
	{//remove first element
		pop_front();
	}
	else
	{
		pos->removeFromList();
		T* pNode = findPredecessor(pos.operator->());
		assert(pNode);
		if (pNode->getNext() == fpLast)
		{//removing last element
			fpLast = pNode;
		}
		pNode->setNext(pos->getNext());
	}
	return next;
}

template<typename T>
typename SLinkedListSet<T>::iterator SLinkedListSet<T>::insert(
	SLinkedListSet<T>::iterator pos,
	T& value)
{
	if (contains_node(&value))
	{
		return pos;
	}
	if (empty() || (pos == begin()))
	{
		push_front(value);
	}
	else if (pos == end())
	{
		push_back(value);
	}
	else
	{
		value.addToList();
		T* pNode = findPredecessor(pos.operator->());
		assert(pNode);
		value.setNext(pNode->getNext());
		pNode->setNext(&value);
	}
	return iterator(&value);
}

template<typename T>
void SLinkedListSet<T>::remove(const T& value)
{
	if (&value == fpFirst)
	{
		pop_front();
	}
	else if (&value == fpLast)
	{
		pop_back();
	}
	else
	{
		const_cast<T&>(value).removeFromList();
		T* pNode = findPredecessor(&value);
		if (pNode)
		{
			pNode->setNext(value.getNext());
		}
	}
}

template <typename T>
bool operator==(
	const SLinkedListSetIterator<T>& x,
	const SLinkedListSetIterator<T>& y);

template <typename T>
bool operator!=(
	const SLinkedListSetIterator<T>& x,
	const SLinkedListSetIterator<T>& y);

template<typename T>
class SLinkedListSetIterator
{
public:
	/** the iterators category */
	typedef SForwardIteratorTag							iterator_category;
	/** value type of iterator */
	typedef typename STypeTraits<T>::value_type			value_type;
	/** reference to value */
	typedef typename STypeTraits<T>::reference			reference;
	/** pointer to value */
	typedef typename STypeTraits<T>::pointer			pointer;
	/** signed integral type */
	typedef typename STypeTraits<T>::difference_type	difference_type;

	SLinkedListSetIterator(T* pValue) :
		fpValue(pValue)
	{}

	SLinkedListSetIterator(const SLinkedListSetIterator& rhs) :
		fpValue(rhs.fpValue)
	{}

	SLinkedListSetIterator& operator=(const SLinkedListSetIterator& rhs)
	{
		fpValue = rhs.fpValue;
		return *this;
	}

	SLinkedListSetIterator& operator++()
	{
		fpValue = fpValue->getNext();
		return *this;
	}

	reference operator*()
	{
		return *fpValue;
	}

	pointer operator->()
	{
		return fpValue;
	}

private:
	friend bool operator==<T>(
		const SLinkedListSetIterator<T>&,
		const SLinkedListSetIterator<T>&);
	friend bool operator!=<T>(
		const SLinkedListSetIterator<T>&,
		const SLinkedListSetIterator<T>&);
	T* fpValue;
};

template<typename T>
inline bool operator==(
	const SLinkedListSetIterator<T>& x,
	const SLinkedListSetIterator<T>& y)
{
	return (x.fpValue == y.fpValue);
}

template<typename T>
inline bool operator!=(
	const SLinkedListSetIterator<T>& x,
	const SLinkedListSetIterator<T>& y)
{
	return !(x == y);
}

#endif /*SLINKEDLIST_H_*/
