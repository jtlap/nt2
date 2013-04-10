//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_GAMMA_HPP_INCLUDED
#include <nt2/toolbox/euler/functions/gamma.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/trunc.hpp>
#include <nt2/include/functions/simd/frac.hpp>
#include <nt2/include/functions/simd/bitwise_ornot.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/sinpi.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return map(functor<tag::gamma_>(), tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::gamma_, tag::cpu_,
                       (A0)(X),
                       ((simd_<floating_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      const double g_p[] = { -1.71618513886549492533811,
                             24.7656508055759199108314,-379.804256470945635097577,
                             629.331155312818442661052,866.966202790413211295064,
                             -31451.2729688483675254357,-36144.4134186911729807069,
                             66456.1438202405440627855 };
      const double g_q[] = { -30.8402300119738975254353,
                             315.350626979604161529144,-1015.15636749021914166146,
                             -3107.77167157231109440444,22538.1184209801510330112,
                             4755.84627752788110767815,-134659.959864969306392456,
                             -115132.259675553483497211 };
      const double g_c[] = { -.001910444077728,8.4171387781295e-4,
                             -5.952379913043012e-4,7.93650793500350248e-4,
                             -.002777777777777681622553,.08333333333333333331554247,
                             .0057083835261 };
      //     const  double g_xbig = 171.624;
      //return map(functor<tag::gamma_>(), tofloat(a0));
      const std::size_t Card = meta::cardinal_of<A0>::value;
      const A0 LOGSQRT2PI =  nt2::log(nt2::sqrt(Two<A0>()*nt2::Pi<A0>()));
      A0 res =  nt2::Nan<A0>();
      A0 fact =  nt2::One<A0>();
      A0 y = a0;
      std::size_t nb1, nb2;
      bA0 lezy =  nt2::is_lez(y);
      if (nt2::inbtrue(lezy) > 0)
      {
        y =  nt2::if_else(lezy, nt2::oneminus(y), y);
        fact =  nt2::if_else(lezy, nt2::Pi<A0>()/nt2::sinpi(y), nt2::One<A0>());
      }
      bA0 lteps = nt2::lt(y, Eps<A0>());
      if ((nb1 = nt2::inbtrue(lteps)) > 0)
      {
        A0 r1 =  nt2::if_nan_else(lteps, nt2::rec(y));
        res &=  r1;
        if(nb1 > Card)
          return finalize(a0, res, fact, lezy);
        y = nt2::if_nan_else(lteps, y);
      }
      bA0 lt12 = lt(y, nt2::splat<A0>(12));
      if ((nb2 = nt2::inbtrue(lt12)) > 0)
      {
        bA0 islt1 = lt(y, nt2::One<A0>());
        A0 y1 = y;
        A0 n =  nt2::minusone(nt2::trunc(y));
        A0 z = nt2::frac(y);
        y =  nt2::oneplus(z);
        A0 xnum =  nt2::Zero<A0>();
        A0 xden =  nt2::One<A0>();
        for (int32_t i = 0; i < 8; ++i)
        {
          xnum = (xnum + nt2::splat<A0>(g_p[i])) * z;
          xden = xden * z +nt2::splat<A0>( g_q[i]);
        }
        A0 r = nt2::oneplus(xnum/xden);
        r =  nt2::if_else(nt2::lt(y1, y), r/y1, r);
        A0 r1 =  r;
        for (int32_t i = 0; i < nt2::maximum(n); ++i)
        {
          //            bA0 t = b_andnot(lt(splat<A0>(i), n), islt1);
          bA0 t = nt2::logical_and(nt2::lt(nt2::splat<A0>(i), n),
                                   nt2::logical_not(islt1)); //logical_andnot
          r *= if_else(t, y, nt2::One<A0>());
          y = seladd(t, y, nt2::One<A0>()) ;
        }
        r =  nt2::if_else(nt2::gt(y1, y), r1, r);
        res =  res & r;
        if(nb1+nb2 > Card) return finalize(a0, res, fact, lezy);
        y = if_nan_else(lteps, y);
      }
      A0 ysq = nt2::sqr(y);
      A0 sum =  nt2::splat<A0>(g_c[6]);
      for (int32_t i = 0; i < 6; ++i) sum = (sum/ysq) + nt2::splat<A0>(g_c[i]);
      sum = (sum/y) - y + LOGSQRT2PI;
      sum += (y - nt2::Half<A0>())*nt2::log(y);
      res = nt2::if_else(eq(a0, nt2::Inf<A0>()), a0, nt2::if_else(lt12, res, nt2::exp(sum)));
      return finalize(a0, res, fact, lezy);
    }
  private :
    template < class AA0, class bAA0 >
      static inline AA0 finalize(const AA0& a0, const AA0& res,
                                 const AA0& fact, const bAA0& lezy)
    {
      bAA0 eqza0 = nt2::is_eqz(a0);
      bAA0 integer =  nt2::logical_and(nt2::is_flint(a0), nt2::logical_not(eqza0));
      return nt2::if_else(eqza0, nt2::rec(a0),
                          nt2::if_else(lezy,
                                       nt2::if_nan_else(integer, fact/res),
                                       res)
                         );
    }

  };
} }
#endif
