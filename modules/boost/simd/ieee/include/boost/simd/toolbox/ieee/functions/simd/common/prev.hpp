//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_PREV_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_PREV_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/fast_frexp.hpp>
#include <boost/simd/include/functions/fast_ldexp.hpp>
#include <boost/simd/include/functions/next.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::prev_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return a0-One<A0>();
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::prev_, tag::cpu_,
                       (A0)(X),
                       ((simd_<floating_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return b_or(-boost::simd::next(-a0), is_nan(a0));
//       typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
//       A0 m;
//       itype expon;
//       boost::fusion::tie(m, expon) = fast_frexp(a0);
//       expon =  seladd(iseq(m, Mhalf<A0>()), expon, Mone<itype>());
//       A0 diff =  fast_ldexp(Mone<A0>(), expon-Nbdigits<A0>());
//       diff = select(iseqz(diff)||iseqz(a0),  Mindenormal<A0>(), diff);
//       return a0+diff;
    }
  };
} } }
#endif
// modified by jt the 04/01/2011
