//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED

#include <boost/simd/swar/functions/split.hpp>
#include <boost/simd/include/functions/simd/split_low.hpp>
#include <boost/simd/include/functions/simd/split_high.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                      )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1, A1& a2) const
    {
      a1 = split_low(a0);
      a2 = split_high(a0);
    }
  };
} } }

#endif
