//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINH_HPP_INCLUDED
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_eqz.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return sinh(tofloat(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
/* __ieee754_sinh(x)//TODO
 * Method :
 * mathematically sinh(x) if defined to be (exp(x)+exp(-x))/2
 *    1. Replace x by |x| (sinh(x) = sinh(-x)).
 *    2.
 *                                                  [ exp(x) - 1 ]^2
 *        0        <= x <= ln2/2  :  sinh(x) := 1 + -------------------
 *                                                   2*exp(x)
 *
 *                                            exp(x) +  1/exp(x)
 *        ln2/2    <= x <= 22     :  sinh(x) := -------------------
 *                                                  2
 *        22       <= x <= lnovft :  sinh(x) := exp(x)/2
 *        lnovft   <= x <= ln2ovft:  sinh(x) := exp(x/2)/2 * exp(x/2)
 *        ln2ovft  <  x     :  sinh(x) := huge*huge (overflow)
 *
 * Special cases:
 *    sinh(x) is |x| if x is +INF, -INF, or NaN.
 *    only sinh(0)=1 is exact for finite x.
 */
        const A0 tmp=exp(a0);
        if (all(gt(abs(a0), Half<A0>())))
          {
            return (tmp-rec(tmp))*Half<A0>();
          }
        else
          {
            return sel(is_eqz(a0), a0, -tmp*nt2::expm1(-(a0+a0))*Half<A0>());
          }
    }
  };
} }


#endif
