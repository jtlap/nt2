//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONSTANT_CONSTANT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONSTANT_CONSTANT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the BOOST_SIMD_CONSTANT_IMPLEMENTATION macro
 */
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/simd/toolbox/operator/functions/map.hpp>

//==============================================================================
// Define hierarchy for constant tags
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct constant_ : elementwise_<T>
  {
    typedef unspecified_<T> parent;
  };
} } }

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::constant_;
} } }

//==============================================================================
/*!
 * Generate a constant function with a given \c NAME tied to a given constant
 * ID \c TAG
 *
 * \param TAG ID of the constant to wrap
 * \param NAME Name of the function to build
 */
//==============================================================================
#define BOOST_SIMD_CONSTANT_IMPLEMENTATION(TAG,NAME)                \
template<class Target> BOOST_DISPATCH_FORCE_INLINE                  \
typename boost::dispatch::meta::                                    \
call<TAG(boost::dispatch::meta::as_<Target>)>::type                 \
NAME()                                                              \
{                                                                   \
  typename boost::dispatch::make_functor<TAG, Target>::type callee; \
  return callee( boost::dispatch::meta::as_<Target>() );            \
}                                                                   \
/**/

#endif
