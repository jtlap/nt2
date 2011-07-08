/*******************************************************************************
 *         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_META_AS_BITS_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_BITS_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// TODO: DEPRECATED FILE TO REMOVE
//////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Sign, class Hierarchy>
  struct as_bits
  {
    typedef union
    {
      T value;
      typename meta::as_integer<T, Sign>::type  bits;
    } type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Sign = unsigned>
  struct  as_bits
        : details::as_bits< typename meta::strip<T>::type
                          , Sign
                          , typename hierarchy_of<T>::type
                          > {};
} } }

#endif

