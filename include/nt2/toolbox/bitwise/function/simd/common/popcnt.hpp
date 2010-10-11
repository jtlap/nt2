//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_POPCNT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_POPCNT_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for popcnt

  /////////////////////////////////////////////////////////////////////////////
  // Compute popcnt(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<popcnt_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0>{};

    ////////////////////////////////////////////////////////////////////////////
    // Functor entry point
    // The straight-line code below, taken from Knuth (pre-fascicle~1a ``Bitwise
    // tricks and techniques'' to volume~4 of ``The Art of Computer Programming'',
    // p.~11), is attributed to D.~B. Gillies and J.~C.~P. Miller. It is faster on
    // the average (assuming non-sparse bitsets), without depending on the number
    // of bits in int_type (except that it is a multiple of 8 less than 256)
    ////////////////////////////////////////////////////////////////////////////
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type    result_type;
      typedef unsigned long long                          sint_type; 
      //      const sint_type b2= ~(~0ull/17ull);
      // |0xF0F0...|; flags positions $\cong4$--$7\pmod8$
      //      const sint_type b3= ~0ull/255;
      // |0x0101...|; flags the low bit of each octet
      const unsigned int high_byte_shift=8*(sizeof(sint_type)-1);

      result_type x = simd::native_cast<result_type>(a0);

      // replace pairs of bits $10\to 01$ and $11\to 10$
      x = x-shri(x & integral_constant<result_type,~(~0ull/3)>(), 1);

      // sideways add 2 groups of pairs of bits to 4-tuples of bits
      x=b_notand(integral_constant<result_type,~(~0ull/5)>(),x)+shri(x & integral_constant<result_type,~(~0ull/5)>(), 2);

      // the sums of octets (bytes) are now in lower 4-tuples of those octets
      x = x + shri(x, 4);

      // add lower 4-tuples of bytes in high octet
      x = b_notand(integral_constant<result_type,~(~0ull/17)>(),x) * integral_constant<result_type,~(~0ull/255)>();

      // extract
      result_type that = shri(x, high_byte_shift);
      return that;
    }
  };
} }

      
#endif
