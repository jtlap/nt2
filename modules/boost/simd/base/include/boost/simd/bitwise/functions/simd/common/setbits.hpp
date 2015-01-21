//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_SETBITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_SETBITS_HPP_INCLUDED

#include <boost/simd/bitwise/functions/setbits.hpp>
#include <boost/simd/include/functions/simd/complement.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/table.hpp>
namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( setbits_, tag::cpu_, (A0)(A1)(A2)(A3)(X)
                          , ((simd_< arithmetic_<A0>, X>))
                            ((simd_< arithmetic_<A1>, X>))
                            ((simd_< uint_<A2>, X>))
                            (scalar_< uint_<A3>>)
                          )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& dest, A1 const& src, A2 at, A3 numbits) const
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type             uiA0;
      uiA0 where_to_insert = shl(splat<uiA0>((( A3(1) << numbits )-A3(1))), at);
      A0 dest_or_where = bitwise_or(dest, where_to_insert);
      A0 src_prep_for_xor = bitwise_and(shl(complement(src), at), where_to_insert);
      return bitwise_xor(dest_or_where, src_prep_for_xor);
    }
  };
} } }

#endif
