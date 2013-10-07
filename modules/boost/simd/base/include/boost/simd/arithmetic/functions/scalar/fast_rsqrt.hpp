//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_RSQRT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fast_rsqrt.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/functions/scalar/rsqrt.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      typedef typename dispatch::meta::as_integer<A0>::type i_t;

      // Quake III Arena fast RSQRT - We do 2 NR steps for precision purpose
      // TODO: Fit this # of NR step into the policy from issue #281
      A0 x2 = a0 * 0.5f;
      A0 y  = bitwise_cast<float>( 0x5f3759df - (bitwise_cast<i_t>(a0) >> 1) );

      y  = y * ( 1.5f - ( x2 * y * y ) );

      return y * ( 1.5f - ( x2 * y * y ) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return simd::rsqrt(a0);
    }
  };

} } }

#endif
