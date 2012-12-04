//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_COSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_COSH_HPP_INCLUDED
#include <nt2/toolbox/hyperbolic/functions/cosh.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/rec.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
/* __ieee754_cosh(x)//TODO
 * Method :
 * mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 *    1. Replace x by |x| (cosh(x) = cosh(-x)).
 *    2.
 *                                                  [ exp(x) - 1 ]^2
 *        0        <= x <= ln2/2  :  cosh(x) := 1 + -------------------
 *                                                   2*exp(x)
 *
 *                                            exp(x) +  1/exp(x)
 *        ln2/2    <= x <= 22     :  cosh(x) := -------------------
 *                                                  2
 *        22       <= x <= lnovft :  cosh(x) := exp(x)/2
 *        lnovft   <= x <= ln2ovft:  cosh(x) := exp(x/2)/2 * exp(x/2)
 *        ln2ovft  <  x     :  cosh(x) := huge*huge (overflow)
 *
 * Special cases:
 *    cosh(x) is |x| if x is +INF, -INF, or NaN.
 *    only cosh(0)=1 is exact for finite x.
 */
      const result_type tmp=exp(tofloat(nt2::abs(a0)));
      return (tmp+rec(tmp))*Half<result_type>();
    }
  };
} }


#endif
