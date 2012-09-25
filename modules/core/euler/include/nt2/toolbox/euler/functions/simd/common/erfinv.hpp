//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_ERFINV_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_ERFINV_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/erfinv.hpp>
#include <nt2/include/functions/simd/polevl.hpp>
#include <nt2/include/functions/simd/erf.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/constants/sqrtpio_2.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfinv_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return erfinv(tofloat(a0));
   }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfinv_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
        static const boost::array<sA0, 4 > a = {{
            sA0(-0.14110320437680104),
            sA0(0.92661860147244357),
            sA0(-1.6601283962374516),
            sA0(0.88622692374517353)
          }};
        static const boost::array<sA0, 5 > b = {{
            sA0( 0.01197270616590528),
            sA0(-0.33198239813321595),
            sA0( 1.46060340345661088),
            sA0(-2.13505380615258078),
            sA0(1)
          }};

        static const boost::array<sA0, 4 > c = {{
            sA0(1.82365845766309853),
            sA0(3.60874665878559364),
            sA0(  -1.87267416351196),
            sA0( -1.994216456587148)
          }};
        static const boost::array<sA0, 3 >d = {{
            sA0(1.81848952562894617),
            sA0(3.74146294065960872),
            sA0(1)
          }};
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      A0 lim = splat<A0>(0.7);
      A0 sign = if_else(nt2::is_ltz(a0), Mone<A0>(), One<A0>());
      bA0 test =  lt(x, lim);
      A0 xx =  sqr(x);
      A0 res =  a0*polevl(xx, a)/polevl(xx, b);
      A0 z = nt2::sqrt(-nt2::log(nt2::oneminus(x)*Half<A0>()));
      res =  if_else(test, res, sign*polevl(z, c)/polevl(z, d));
      res -= (nt2::erf(res)-a0)*Sqrtpio_2<A0>()/nt2::exp(-nt2::sqr(res));
      res -= (nt2::erf(res)-a0)*Sqrtpio_2<A0>()/nt2::exp(-nt2::sqr(res));
      return if_else(eq(x, One<A0>()), a0*Inf<A0>(), res);
   }
  };


} }
#endif
