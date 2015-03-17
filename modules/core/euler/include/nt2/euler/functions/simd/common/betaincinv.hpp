//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_BETAINCINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_BETAINCINV_HPP_INCLUDED

#include <nt2/euler/functions/betaincinv.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/betaln.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functions/simd/maxmag.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( betaincinv_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>, X>))
                              ((simd_< floating_<A0>, X >))
                              ((simd_< floating_<A0>, X >))
                            )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&p, const A0& a,  const A0 &b)
    {
      result_type x;
      result_type a1 = minusone(a);
      result_type b1 = minusone(b);
      const  result_type epsi = Ten<result_type>()*Eps<result_type>();
      x = if_else (logical_and(ge(a, One<result_type>()),  ge(b, One<result_type>())),
                   compute_large(p, a, b),
                   compute_small(p, a, b)
                  );

      result_type afac = -betaln(a, b);;
      for (std::size_t j=0; j < 10; ++j)
      {
//          if (x == 0. || x == 1.) return x; // a or b too small for accurate calculation.
        result_type err = betainc(x, a,b) - p;
        result_type t = exp(fma(a1, log(x), b1*log1p(-x)) + afac);
        result_type u = err/t; // Halley:
        t = u/fam(One<result_type>(), Mhalf<result_type>(),
                  nt2::min(One<result_type>(),u*(a1/x - b1/(oneminus(x)))));
        x -= t;
        result_type tt = if_else(ge(x, One<result_type>()), oneplus(t), t);
        x = if_else(logical_and(is_lez(x), ge(x, One<result_type>())), average(x, tt), x);

        if (all(le(nt2::abs(t), epsi*x)) && j) break;
      }
      return if_zero_else(is_lez(p)
                         , if_else(ge(p, One<result_type>()), One<result_type>(),
                                       x)
                         );
    }
  private:
    static BOOST_FORCEINLINE
      result_type compute_large(const A0&p, const A0& a,  const A0 &b)
    {
      //  Set initial guess.
      const result_type FiveoSix = nt2::splat<result_type>(5./6.);
      result_type a1 = minusone(a);
      result_type b1 = minusone(b);
      result_type pp = if_else(lt(p, Half<result_type>()), p, oneminus(p));
      result_type t = sqrt(Mtwo<result_type>()*log(pp));
      result_type x = fma(t, splat<result_type>(0.27061), splat<result_type>(2.30753))/
        fma(t, fma(t, splat<result_type>(0.04481), splat<result_type>(0.99229)),
            One<result_type>()) - t;
      x = negif(lt(p, Half<result_type>()), x);
      result_type al = (sqr(x)-Three<result_type>())*Oneo_6<result_type>();
      result_type r2a1 = rec(a+a1);
      result_type r2b1 = rec(b+b1);
      result_type h = Two<result_type>()*rec(r2a1+r2b1);
      result_type w = (x*sqrt(al+h)/h)-(r2b1-r2a1)*(al+FiveoSix-Twothird<result_type>()/h);
      return a/fam(a, b, exp(w+w));
    }

    static BOOST_FORCEINLINE
      result_type compute_small(const A0&p, const A0& a,  const A0 &b)
    {
      result_type lna = log(a/(a+b));
      result_type lnb = log(b/(a+b));
      result_type t = exp(a*lna)/a;
      result_type u = exp(b*lnb)/b;
      result_type w = t+u;
      auto test = lt(p, t/w);
      result_type z = if_else (test, a*w*p, b*w*oneminus(p));
      result_type po = pow(z, rec(if_else (test, a, b)));
      return if_else(test, po, oneminus(po));
    }

  };
} }

#endif
