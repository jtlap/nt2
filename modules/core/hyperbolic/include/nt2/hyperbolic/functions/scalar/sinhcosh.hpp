//===============================================================================
//       Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//       Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//        Distributed under the Boost Software License, Version 1.0.
//               See accompanying file LICENSE.txt or copy at
//                   http://www.boost.org/LICENSE_1_0.txt
//===============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINHCOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINHCOSH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/sinhcosh.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/expm1.hpp>
#include <nt2/include/functions/scalar/negif.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/is_negative.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::sinhcosh_, tag::cpu_,(A0)
                            , ((scalar_<floating_<A0> >))
                               ((scalar_<floating_<A0> >))
                               ((scalar_<floating_<A0> >))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      a2 =  nt2::abs(a0);
      a1 = a0;
      if (a2 == Inf<A0>()) return;
      const A0 u = expm1(a2);
      const A0 up1 = oneplus(u);
      const A0 tmp =u/up1;
      a1 = negif(is_negative(a0), Half<A0>()*tmp*(oneplus(up1)));
      a2 = oneplus(Half<A0>()*tmp*u);
    }
  };

} }
#endif
