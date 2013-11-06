//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_FAST_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_FAST_REC_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fast_rec.hpp>
#include <boost/simd/include/functions/simd/raw_rec.hpp>
#include <boost/simd/include/functions/simd/fnms.hpp>
#include <boost/simd/include/functions/simd/fma.hpp>
#include <boost/simd/include/constants/one.hpp>

namespace boost { namespace simd { namespace ext
{
  // Single precision fast_rec is computable from the raw_rec + 1 NR step
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION (  boost::simd::tag::fast_rec_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< single_<A0>, X >))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Estimation x ~= 1/X
      A0  inv   = raw_rec( a0 );

      // Newton-Raphson: 1/X ~= x*(1-a0*x) + x
      return fma(fsm(One<A0>(), a0, inv), inv, inv);
    }
  };
} } }

#endif
