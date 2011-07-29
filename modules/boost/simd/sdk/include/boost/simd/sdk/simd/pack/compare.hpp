/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_COMPARE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_COMPARE_HPP_INCLUDED

namespace boost { namespace simd
{
  #define BOOST_SIMD_COMPARE(Op)                                                \
  template<class X,class Y, class T, class C>                                 \
  bool operator Op ( expression<X,T,C> const& x, expression<Y,T,C> const& y ) \
  {                                                                           \
    pack<T,C::value> a(x),b(y);                                               \
    return a.value().value() Op b.value().value();                            \
  }                                                                           \
  template<class X,class Y, class T, class C>                                 \
  bool operator Op ( X const& x, expression<Y,T,C> const& y )                 \
  {                                                                           \
    pack<T,C::value> a(x),b(y);                                               \
    return a.value().value() Op b.value().value();                            \
  }                                                                           \
  template<class X,class Y, class T, class C>                                 \
  bool operator Op ( expression<X,T,C> const& x, Y const& y )                 \
  {                                                                           \
    pack<T,C::value> a(x),b(y);                                               \
    return a.value().value() Op b.value().value();                            \
  }                                                                           \
  template<class T, std::size_t C>                                            \
  bool operator Op ( pack<T,C> const& x, pack<T,C> const& y )                 \
  {                                                                           \
    return x.value().value() Op y.value().value();                            \
  }                                                                           \
  template<class X,class T, std::size_t C>                                    \
  bool operator Op ( X const& x, pack<T,C> const& y )                         \
  {                                                                           \
    pack<T,C> a(x);                                                           \
    return a.value().value() Op y.value().value();                            \
  }                                                                           \
  template<class Y, class T, std::size_t C>                                   \
  bool operator Op ( pack<T,C> const& x, Y const& y )                         \
  {                                                                           \
    pack<T,C> b(y);                                                           \
    return x.value().value() Op b.value().value();                            \
  }                                                                           \
  /**/

  BOOST_SIMD_COMPARE( == )
  BOOST_SIMD_COMPARE( != )
  BOOST_SIMD_COMPARE( >  )
  BOOST_SIMD_COMPARE( <  )
  BOOST_SIMD_COMPARE( >= )
  BOOST_SIMD_COMPARE( <= )

  #undef BOOST_SIMD_COMPARE
} }
#endif
