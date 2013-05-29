//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVS_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/divs.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/complement.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0/a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                            , ((simd_<uint_<A0>,X>))
                              ((simd_<uint_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      const bA0 iseqza1 = is_eqz(a1);
      const A0 aa1 =  seladd(iseqza1, a1, One<A0>());
      const A0 r1 = a0/aa1; //a1!= 0
      const A0 r2 = if_zero_else(is_eqz(a0),Valmax<A0>());
      return if_else(iseqza1, r2, r1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                            , ((simd_<int_<A0>,X>))
                              ((simd_<int_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      const bA0 iseqza1 = is_eqz(a1);
      const A0 c = ~(genmask(a0-Valmin<A0>())|genmask(a1+One<A0>()));
      const A0 aa1 = seladd(iseqza1, a1, One<A0>());
      const A0 r1 = (a0-c)/aa1; //a1!= 0
      const A0 r2 = ((genmask(is_ltz(a0))^Valmax<A0>())) & genmask(is_nez(a0)); // r2 is Valmin Valmax or 0
      return if_else(iseqza1, r2, r1);
    }
  };
} } }

#endif
