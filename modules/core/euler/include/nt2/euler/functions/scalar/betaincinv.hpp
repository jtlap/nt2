//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_BETAINCINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_BETAINCINV_HPP_INCLUDED

#include <nt2/euler/functions/betaincinv.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/betaln.hpp>
#include <nt2/include/functions/scalar/betainc.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/functions/scalar/is_lez.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/scalar/min.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/unary_minus.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/oneo_6.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( betaincinv_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0 &p, const A0&a, const A0& b)
    {
      result_type x;
      const  result_type epsi = Ten<result_type>()*Eps<result_type>();
      result_type a1 = minusone(a);
      result_type b1 = minusone(b);
      if (is_lez(p)) return Zero<result_type>();
      if (ge(p, One<result_type>())) return One<result_type>();
      if (ge(a, One<result_type>()) && ge(b, One<result_type>()))
      {
        //  Set initial guess.
        result_type pp = (lt(p, Half<result_type>())) ? p : oneminus(p);
        result_type t = sqrt(Mtwo<result_type>()*log(pp));
        x = fma(t, result_type(0.27061), result_type(2.30753))/
          fma(t, fma(t, result_type(0.04481), result_type(0.99229)),
              One<result_type>()) - t;
        if (lt(p, Half<result_type>())) x = -x;
        result_type al = (sqr(x)-Three<result_type>())*Oneo_6<result_type>();
        result_type r2a1 = rec(a+a1);
        result_type r2b1 = rec(b+b1);
        result_type h = Two<result_type>()*rec(r2a1+r2b1);
        result_type w = (x*sqrt(al+h)/h)-(r2b1-r2a1)*(al+5./6.-2./(3.*h));
        x = a/fam(a, b, exp(w+w));
      }
      else
      {
        result_type lna = log(a/(a+b));
        result_type lnb = log(b/(a+b));
        result_type t = exp(a*lna)/a;
        result_type u = exp(b*lnb)/b;
        result_type w = t+u;
        if (lt(p, t/w))
          x = pow(a*w*p,rec(a));
        else
          x = 1. - pow(b*w*oneminus(p),rec(b));
      }
      result_type afac = -betaln(a, b);; ///-gammaln(a)-gammaln(b)+gammaln(a+b);
      for (std::size_t j=0; j < 10; ++j) {
        if (x == 0. || x == 1.) return x; // a or b too small for accurate calculation.
        result_type err = betainc(x, a,b) - p;
        result_type t = exp(fma(a1, log(x), b1*log1p(-x)) + afac);
        result_type u = err/t; // Halley:
        x -= (t = u/fam(One<result_type>(), Mhalf<result_type>(),
                        nt2::min(One<result_type>(),u*(a1/x - b1/(oneminus(x))))));
        if (is_lez(x)) x = average(x, t);// Bisect if x tries to go <=  or >=  1
        if (ge(x, One<result_type>())) x = average(oneplus(x), t);
        if (nt2::abs(t) < epsi*x && j) return x;
      }
      return x;
    }
  };
} }

#endif
