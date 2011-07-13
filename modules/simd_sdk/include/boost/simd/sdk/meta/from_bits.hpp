/*******************************************************************************
 *         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_META_FROM_BITS_HPP_INCLUDED
#define BOOST_SIMD_META_FROM_BITS_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// TODO DEPRECATE THIS FILE USE BITWISE_CAST
//////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T, class Sign, class Hierarchy>
  struct from_bits
  {
    typedef typename meta::as_integer<T, Sign>::type  bits_type;
    typedef typename meta::as_integer<T, Sign>::type  value_type;

    typedef union
    {
      typename meta::as_integer<T, Sign>::type  bits;
      T                                          value;
    } type;
  };
} } }

namespace boost { namespace simd { namespace meta
{
  template<class T, class Sign = unsigned>
  struct  from_bits
        : details::from_bits< typename strip<T>::type
                            , Sign
                            , typename hierarchy_of<T>::type
                            > {};
} } }

#endif

