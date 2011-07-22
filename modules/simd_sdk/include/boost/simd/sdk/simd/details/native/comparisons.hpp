/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_COMPARISONS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_COMPARISONS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Setup SIMD extension specific boolean operations
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/toolbox/operator/specific/compare_tags.hpp>

#define BOOST_SIMD_MAKE_NATIVE_OP(TAG,OP)                                \
template<class T,class X> inline                                         \
typename boost::dispatch::meta::call<TAG(native<T,X>,native<T,X>)>::type \
OP(native<T,X> const& a0, native<T,X> const& a1)                         \
{                                                                        \
  typename boost::dispatch::make_functor<TAG,T>::type callee;            \
  return callee(a0,a1);                                                  \
}                                                                        \
/**/

namespace boost { namespace simd
{
  BOOST_SIMD_MAKE_NATIVE_OP( boost::dispatch::tag::compare_equal_        , operator== )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::dispatch::tag::compare_not_equal_    , operator!= )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::dispatch::tag::compare_less_         , operator<  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::dispatch::tag::compare_greater_      , operator>  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::dispatch::tag::compare_less_equal_   , operator<= )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::dispatch::tag::compare_greater_equal_, operator>= )
} }

#undef BOOST_SIMD_MAKE_NATIVE_OP

#endif
