//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOINTS_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/toints.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/functions/toint.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/if_zero_else.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::toints_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<integer_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    #ifdef BOOST_PROTO_STRICT_RESULT_OF
    result_type
    #else
    A0 const&
    #endif
    operator()(A0 const& a0) const
    {
      return a0;
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::toints_, tag::cpu_,
                                     (A0)(X)
                                   , ((simd_<floating_<A0>,X>))
                                   )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 aa0 = if_zero_else(is_nan(a0), a0);
      result_type that = toint(aa0);
      return if_else(eq(aa0, Inf<A0>()), Inf<result_type>(),
                     if_else(eq(aa0, Minf<A0>()), Minf<result_type>(),
                             that)
                    );

    }
  };
} } }

#endif
