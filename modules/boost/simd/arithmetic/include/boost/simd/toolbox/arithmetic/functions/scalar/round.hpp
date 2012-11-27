//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ROUND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ROUND_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/round.hpp>
#include <boost/simd/include/constants/twotonmb.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::round_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const result_type v = boost::simd::abs(a0);
      const result_type t2n = boost::simd::Twotonmb<result_type>();
      volatile result_type d0 = (v+t2n);
      volatile result_type d = (d0-t2n);
      d = (v < t2n)?d:v;
      return a0 < 0? -d : d;
    }
  };
} } }


#endif
