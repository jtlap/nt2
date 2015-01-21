//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_SETBITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_SETBITS_HPP_INCLUDED

#include <boost/simd/bitwise/functions/setbits.hpp>
#include <boost/simd/include/functions/scalar/complement.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( setbits_, tag::cpu_, (A0)(A1)(A2)(A3)
                          , (scalar_< arithmetic_<A0> >)
                            (scalar_< arithmetic_<A1> >)
                            (scalar_< uint_<A2>>)
                            (scalar_< uint_<A3>>)
                          )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& dest, A1 const& src,
                                             A2 at, A3 numbits) const
    {
      A0 where_to_insert = (( 1 << numbits )-1)<<at;
      A0 dest_or_where = where_to_insert|dest;
      A0 src_prep_for_xor = (~src<<at) & where_to_insert;
      A0 value = (dest_or_where)^(src_prep_for_xor);
      return value;
    }
  };
} } }

#endif
