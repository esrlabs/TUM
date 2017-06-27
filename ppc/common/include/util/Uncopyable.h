/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains helpers to make C++ classes uncopyable, i.e. declare copy
 * constructor and assignment operator private.
 * \file	Uncopyable.h
 */
#ifndef UNCOPYABLE_H_
#define UNCOPYABLE_H_

/**
 * The macro MAKE_UNCOPYABLE expands to a declaration of copy constructor and
 * assignment operator.
 * \par	Usage example
 * \code
 * class MyClass
 * {
 * 		MAKE_UNCOPYABLE(MyClass)
 * public:
 *		//...
 * };
 * \endcode
 */
#ifdef MAKE_UNCOPYABLE
#error "MAKE_UNCOPYABLE was already defined!"
#endif
// PRQA S 1030 3
#define MAKE_UNCOPYABLE(TypeName)		\
	TypeName(const TypeName&);			\
	TypeName& operator=(const TypeName&);

namespace common
{

/**
 * Inheriting from Uncopyable makes sure that no copies of any subclass
 * are instantiated accidently because the C++ compiler will raise an error.
 *
 * \author	oliver.mueller
 */
class Uncopyable
{
protected:
	Uncopyable(){}

private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

}//namespace common

#endif /*UNCOPYABLE_H_*/
