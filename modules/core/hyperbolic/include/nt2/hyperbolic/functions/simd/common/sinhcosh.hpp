//===============================================================================
//       Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//       Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//        Distributed under the Boost Software License, Version 1.0.
//               See accompanying file LICENSE.txt or copy at
//                   http://www.boost.org/LICENSE_1_0.txt
//===============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHCOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHCOSH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/sinhcosh.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/is_negative.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::sinhcosh_, tag::cpu_,(A0)(X)
                            , ((simd_<floating_<A0>,X>))
                               ((simd_<floating_<A0>,X>))
                               ((simd_<floating_<A0>,X>))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_logical<A0>::type ltype;
      A0 a00 =  nt2::abs(a0);
      ltype test =  eq(a00, Inf<A0>());
      const A0 u = nt2::expm1(a00);
      const A0 up1 = oneplus(u);
      const A0 tmp =u/up1;
      a1 = negif(is_negative(a0), if_else(test, a00, Half<A0>()*tmp*(oneplus(up1))));
      a2 = if_else(test, a00, oneplus(Half<A0>()*tmp*u));
    }
  };

} }
#endif
