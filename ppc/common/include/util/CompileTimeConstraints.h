/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#ifndef COMPILETIMECONSTRAINTS_H_
#define COMPILETIMECONSTRAINTS_H_

#include "commonTypes.h"

#define ZGW_JOIN( X, Y ) ZGW_DO_JOIN( X, Y )
#define ZGW_DO_JOIN( X, Y ) ZGW_DO_JOIN2(X,Y)
#define ZGW_DO_JOIN2( X, Y ) X##Y

namespace common
{
template <bool x> struct STATIC_ASSERTION_FAILURE;
template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

# define ECU_STATIC_ASSERT( B ) \
    typedef char ZGW_JOIN(zgw_static_assert_typedef_, __LINE__) \
        [ ::common::STATIC_ASSERTION_FAILURE< (bool)( B ) >::value ]

template<bool Condition>
struct CompileTimeError;

template<>
struct CompileTimeError<false> {};

/**
 * STATIC_CHECK will fail when expr evaluates to true
 */
#define STATIC_CHECK(msg, expr) \
    { common::CompileTimeError<(expr)> ERROR_##msg; (void)ERROR_##msg; }

/**
 * STATIC_ASSERT will fail when expr evaluates to false
 * simple usage: STATIC_ASSERT(too_bad_static_assert_failed, 2 > 3)
 */
#define STATIC_ASSERT(msg, expr) \
    { common::CompileTimeError<!(expr)> ERROR_##msg; (void)ERROR_##msg; }

/**
 * another example-setup for compile-time-check: a class only has to inherit from this constraint,
 * so the constructor of this Constraint has to be compiled and the static check is executed
 * by the compiler.
 * will only compile if ACTUAL_SIZE <= ALLOWED_SIZE
 *
 * the argument passed to the STATIC_CHECK-macro can be any allowed C++-identifier,
 */
template<uint32 ACTUAL_SIZE, uint32 ALLOWED_SIZE>
struct ValidSizeConstraint
{
   	static void constraint()
   	{
   		STATIC_CHECK(fuck_allowed_size_is_too_small,
   					(ACTUAL_SIZE > ALLOWED_SIZE));
   	}
   	ValidSizeConstraint()
   	{
      	void (*p)() = constraint;
      	(*p)();//call function, only to make compiler warning about unused variable go away, will get optimized away
  	}
};

/**
 * static checks
 * usage:
 * struct B {}; struct D : B { };
 * ...Derived_from<D,B>();
 */
template<class T, class B> struct Derived_from
{
	static void constraints(T* p) { B* pb = p; pb = pb;}
	Derived_from() { void(*p)(T*) = constraints; p = p;}
};

template<class T1, class T2> struct Can_copy
{
	static void constraints(T1 a, T2 b) { T2 c = a; b = a; c = a; b = a; }
	Can_copy() { void(*p)(T1,T2) = constraints;}
};

template<class T1, class T2 = T1> struct Can_compare
{
	static void constraints(T1 a, T2 b) { a==b; a!=b; a<b; }
	Can_compare() { void(*p)(T1,T2) = constraints;}
};
}//namespace common

#endif /*COMPILETIMECONSTRAINTS_H_*/
