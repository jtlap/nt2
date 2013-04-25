//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_IROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_IROUND2EVEN_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/iround2even.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/simd/toint.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/round2even.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::iround2even_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<arithmetic_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return a0; }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::iround2even_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<floating_<A0>,X>))
                                   )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type sr_type;
      A0 tmp = boost::simd::round2even(a0);
      const A0 vx = boost::simd::splat<A0>(boost::simd::Valmax<sr_type>());
      const A0 vn = boost::simd::splat<A0>(boost::simd::Valmin<sr_type>());
      return boost::simd::if_else(
        boost::simd::gt(tmp, vx), boost::simd::Valmax<result_type>(),
        boost::simd::if_else(boost::simd::lt(tmp, vn), boost::simd::Valmin<result_type>(),
                             boost::simd::toint(tmp)
                            )
      );
    }
  };
} } }


#endif
