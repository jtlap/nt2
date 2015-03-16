//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_BETAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_BETAINC_HPP_INCLUDED

#include <nt2/euler/functions/betainc.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/betaln.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functions/simd/maxmag.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( betainc_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>, X>))
                              ((simd_< floating_<A0>, X >))
                              ((simd_< floating_<A0>, X >))
                            )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&x, const A0& a,  const A0 &b)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      result_type bt=exp(fma(a, log(x), b*log1p(-x))-betaln(a, b));
      bA0 test = lt(x, oneplus(a)/(a+b+Two<result_type>()));
      result_type xx = if_else(test, x, oneminus(x));
      result_type aa = if_else(test, a, b);
      result_type bb = if_else(test, b, a);
      result_type res =  bt*betacf(xx,aa,bb)/aa;
      return if_nan_else(logical_or(is_ltz(xx), gt(xx, One<result_type>())),
                         if_zero_else(is_eqz(xx),
                                      if_else(eq(xx, One<result_type>()),
                                              One<result_type>(),
                                              if_else(test, res, oneminus(res)
                                                     )
                                             )
                                     )
                        );
    }
  private :
    static BOOST_FORCEINLINE result_type betacf(const A0& x, const A0& a,  const A0& b)
    {
      // continued fraction for incomplete Beta function, used by betainc
      const  std::size_t itmax = 100;
      const  result_type epsi = Ten<result_type>()*Eps<result_type>();
      const  result_type fpmin = sqr(Eps<result_type>());
      result_type qab = a+b;
      result_type qap = oneplus(a);
      result_type qam = minusone(a);
      result_type c = One<result_type>();
      result_type d = rec(maxmag(oneminus(qab*x/qap), fpmin));
      result_type h = d;
      for (std::size_t m=1; m<=itmax; ++m)
      {
        result_type vm = nt2::splat<result_type>(m);
        result_type vm2 = vm+vm;
        result_type aa=vm*(b-vm)*x/((qam+vm2)*(a+vm2));
        d = rec(maxmag(fma(aa, d, One<result_type>()), fpmin));
        c = maxmag(fma(aa, rec(c), One<result_type>()), fpmin);
        h *= d*c;
        aa = -(a+vm)*(qab+vm)*x/((a+vm2)*(qap+vm2));
        d = rec(maxmag(fma(aa, d, One<result_type>()), fpmin));
        c = maxmag(fma(aa, rec(c), One<result_type>()), fpmin);
        result_type del=d*c;
        h *= del;
        if (all(lt(nt2::abs(oneminus(del)), epsi))) return h; //Are we done?
      }
      NT2_WARNING ( true
                  , "betainc evaluation by a continuous fraction has not converged after 100 iterations."
                  );
      return h;
    }

  };
} }

#endif
