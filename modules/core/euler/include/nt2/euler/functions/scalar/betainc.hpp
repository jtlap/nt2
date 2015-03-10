//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_BETAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_BETAINC_HPP_INCLUDED

#include <nt2/euler/functions/betainc.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/betaln.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/maxmag.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/error/warning.hpp>


namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( betainc_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0 &x, const A0&a, const A0& b)
    {
      if (x < 0.0 || x > 1.0) return Nan<result_type>();
      if (x == 0.0) return Zero<result_type>();
      if (x == 1.0) return One<result_type>();
      result_type bt=exp(fma(a, log(x), b*log1p(-x))-betaln(a, b));

      if (x < oneplus(a)/(a+b+Two<result_type>()))
      {
        return (bt*betacf(x,a,b)/a);
      }
      else
      {
        return oneminus(bt*betacf(oneminus(x), b,a)/b);
      }
    }
  private :
    static BOOST_FORCEINLINE result_type betacf(const A0& x, const A0& a,  const A0& b)
    {
      // continued fraction for incomplete Beta function, used by betainc
      const  std::size_t itmax = 100;
      const  result_type epsi = result_type(10)*Eps<result_type>();
      const  result_type fpmin = sqr(Eps<result_type>());
      result_type qab = a+b;
      result_type qap = oneplus(a);
      result_type qam = minusone(a);
      result_type c = One<result_type>();
      result_type d = rec(maxmag(oneminus(qab*x/qap), fpmin));
      result_type h = d;
      for (std::size_t m=1; m<=itmax; ++m)
      {
        result_type m2 = m+m;
        result_type aa=m*(b-m)*x/((qam+m2)*(a+m2));
        d = rec(maxmag(fma(aa, d, One<result_type>()), fpmin));
        c = maxmag(fma(aa, rec(c), One<result_type>()), fpmin);
        h *= d*c;
        aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
        d = rec(maxmag(fma(aa, d, One<result_type>()), fpmin));
        c = maxmag(fma(aa, rec(c), One<result_type>()), fpmin);
        result_type del=d*c;
        h *= del;
        if (nt2::abs(oneminus(del)) < epsi) return h; //Are we done?
      }
      NT2_WARNING ( true
                  , "betainc evaluation by a continuous fraction has not converged after 100 iterations."
                  );
      return h;
    }

  };
} }

#endif
