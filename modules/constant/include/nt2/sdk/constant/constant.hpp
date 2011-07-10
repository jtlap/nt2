//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONSTANT_CONSTANT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_CONSTANT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the NT2_CONSTANT_IMPLEMENTATION macro
 */
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/functor/functor.hpp>
#define STRUCT(NAME)						\
  template < class T1 > struct _##NAME{				\
    const T1 operator()()const {return nt2::NAME<T1>(); }	\
  };								\
  /**/

//==============================================================================
/*!
 * Generate a constant function with a given \c NAME tied to a given constant
 * ID \c TAG
 *
 * \param TAG ID of the constant to wrap
 * \param NAME Name of the function to build
 */
//==============================================================================
#define NT2_CONSTANT_IMPLEMENTATION(TAG,NAME)           \
template<class Target> inline                           \
typename meta::call<TAG(nt2::meta::as_<Target>)>::type  \
NAME()                                                  \
{                                                       \
  typename nt2::make_functor<TAG, Target>::type callee; \
  return callee( nt2::meta::as_<Target>() );            \
}							\
  STRUCT(NAME)						\
/**/

#endif
