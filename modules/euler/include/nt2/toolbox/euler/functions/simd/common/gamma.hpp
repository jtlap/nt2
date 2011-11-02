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
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/frac.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/if_nan_else.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/sdk/simd/logical.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
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
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is floating_
  /////////////////////////////////////////////////////////////////////////////
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
      const int32_t Card = meta::cardinal_of<A0>::value;
      const A0 LOGSQRT2PI =  log(sqrt(Two<A0>()*Pi<A0>())); 
      A0 res =  Nan<A0>();
      A0 fact =  One<A0>();
      A0 y = a0;
      int32_t nb1, nb2;
      bA0 lezy =  is_lez(y);
      if (nbtrue(lezy) > 0)
        {
          y =  sel(lezy, oneminus(y), y); 
          fact =  sel(lezy, Pi<A0>()/sinpi(y), One<A0>());
        }
      bA0 lteps = lt(y, Eps<A0>());
      if ((nb1 = nbtrue(lteps)) > 0)
        {
          A0 r1 =  if_nan_else(lteps, rec(y));//b_ornot(rec(y), lteps);
          res &=  r1;
          if(nb1 > Card)
            return finalize(a0, res, fact, lezy);
          y = if_nan_else(lteps, y); 
        }
      bA0 lt12 = lt(y, splat<A0>(12));   
      if ((nb2 = nbtrue(lt12)) > 0)
        {
          bA0 islt1 = lt(y, One<A0>());
          A0 y1 = y; 
          A0 n =  minusone(trunc(y));
          A0 z = frac(y); 
          y =  oneplus(z);
          A0 xnum =  Zero<A0>();
          A0 xden =  One<A0>();
          for (int32_t i = 0; i < 8; ++i)
            {
            xnum = (xnum + splat<A0>(g_p[i])) * z;
            xden = xden * z +splat<A0>( g_q[i]);            
            }
          A0 r = oneplus(xnum/xden);
          r =  sel(lt(y1, y), r/y1, r);
          A0 r1 =  r;
          for (int32_t i = 0; i < maximum(n); ++i)
            {
            bA0 t = b_andnot(lt(splat<A0>(i), n), islt1); 
            r *= sel(t, y, One<A0>());
            y = seladd(t, y, One<A0>()) ;
            }
          r =  sel(gt(y1, y), r1, r); 
          res =  res & r;
          if(nb1+nb2 > Card) return finalize(a0, res, fact, lezy);
          y = if_nan_else(lteps, y); 
        }
      A0 ysq = sqr(y);
      A0 sum =  splat<A0>(g_c[6]);
      for (int32_t i = 0; i < 6; ++i) sum = (sum/ysq) + splat<A0>(g_c[i]);
      sum = (sum/y) - y + LOGSQRT2PI;
      sum += (y - Half<A0>())*log(y);
      res = sel(eq(a0, Inf<A0>()), a0, sel(lt12, res, exp(sum)));
      return finalize(a0, res, fact, lezy);      
      }
  private :
    template < class AA0, class bAA0 >
      static inline AA0 finalize(const AA0& a0, const AA0& res,
                         const AA0& fact, const bAA0& lezy)
      {
      bAA0 eqza0 = is_eqz(a0); 
      bAA0 integer =  b_andnot(is_flint(a0), eqza0);
      return sel(eqza0, rec(a0), sel(lezy, if_nan_else(integer, fact/res), res));
      }
    
  };
} }
#endif
