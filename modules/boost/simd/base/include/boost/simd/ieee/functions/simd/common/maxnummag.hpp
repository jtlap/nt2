//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_MAXNUMMAG_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_MAXNUMMAG_HPP_INCLUDED
#include <boost/simd/ieee/functions/maxnummag.hpp>
#include <boost/simd/include/functions/simd/maxmag.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::maxnummag_, tag::cpu_,
                            (A0)(X),
                            ((simd_<integer_<A0>,X>))
                            ((simd_<integer_<A0>,X>))
                           )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return maxmag(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::maxnummag_, tag::cpu_,
                            (A0)(X),
                            ((simd_<unspecified_<A0>,X>))
                            ((simd_<unspecified_<A0>,X>))
                           )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 a = select(is_nan(a0),a1,a0);
      const A0 b = select(is_nan(a1),a0,a1);
      return maxmag(a, b);
    }
  };
} } }
#endif
