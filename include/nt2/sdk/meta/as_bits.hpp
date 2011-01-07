/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_AS_BITS_HPP_INCLUDED
#define NT2_SDK_META_AS_BITS_HPP_INCLUDED

#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
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
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Take a value and provide access to its bits
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Sign = unsigned>
  struct  as_bits
        : details::as_bits< typename meta::strip<T>::type
                          , Sign
                          , typename hierarchy_of<T>::type
                          > {};
} }

#endif

