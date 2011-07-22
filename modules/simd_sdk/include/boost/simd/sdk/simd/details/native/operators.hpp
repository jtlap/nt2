/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/config/attributes.hpp>

#define BOOST_SIMD_MAKE_NATIVE_OP(TAG,OP)                                  \
template<class T1, class T2,class X> BOOST_SIMD_FORCE_INLINE               \
typename boost::dispatch::meta::call<TAG(native<T1,X>,native<T2,X>)>::type \
OP(native<T1,X> const& a0, native<T2,X> const& a1)                         \
{                                                                          \
  typename boost::dispatch::make_functor<TAG,T1>::type callee;             \
  return callee(a0,a1);                                                    \
}                                                                          \
/**/

namespace boost { namespace simd
{
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::bitwise_and     , operator&  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::bitwise_or      , operator|  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::bitwise_xor     , operator^  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::logical_and     , operator&& )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::logical_or      , operator|| )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::plus            , operator+  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::minus           , operator-  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::divides         , operator/  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::multiplies      , operator*  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::modulus         , operator%  )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::shift_left      , operator<< )
  BOOST_SIMD_MAKE_NATIVE_OP( boost::proto::tag::shift_right     , operator>> )
} }

#undef BOOST_SIMD_MAKE_NATIVE_OP

#endif
