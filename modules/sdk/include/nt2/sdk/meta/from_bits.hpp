/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_FROM_BITS_HPP_INCLUDED
#define NT2_SDK_META_FROM_BITS_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Take a bit pattern and turn it into a value
// See: http://nt2.metascale.org/sdk/meta/traits/from_bits.html
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
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
} }

namespace nt2 { namespace meta
{
  template<class T, class Sign = unsigned>
  struct  from_bits
        : details::from_bits< typename strip<T>::type
                            , Sign
                            , typename hierarchy_of<T>::type
                            > {};
} }

#endif

