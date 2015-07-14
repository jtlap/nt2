//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_SINC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_SINC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sinc.hpp>
#include <nt2/trig_derivatives/functions/details/sinc_kernel.hpp>
#include <nt2/include/functions/simd/cospi.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sinc.hpp>
#include <nt2/include/functions/simd/sincos.hpp>
#include <nt2/include/functions/simd/fms.hpp>
#include <nt2/include/functions/simd/fnma.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>


namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( sinc_, tag::cpu_
                              , (order)(A0)
                              , (unspecified_<order>)
                                (generic_<unspecified_<A0>>)
                              )
    {
      typedef A0                                            result_type;
      typedef typename meta::scalar_of<A0>::type                    sA0;
      BOOST_FORCEINLINE result_type operator()(const order&
                                              , const A0& u) const
      {
        return compute(order(), u);
      }
    private:
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>
                                           , const A0& u) const
      {
        return nt2::sinc(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        A0 s, c;
        sincos(u, s, c);
        return if_zero_else(is_eqz(u), fms(u, c, s)/sqr(u));
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        A0 s, c;
        sincos(u, s, c);
        A0 u2 = sqr(u);
        return  if_else(is_eqz(u), -Third<A0>(), fnma(u2-Two<A0>(), s, Two<A0>()*u*c)/(u2*u));
      }

      template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        container::table<sA0> p, q;
        details::sinc_kernel<P, A0>::sinc_pl(p, q);
        A0 s, c;
        sincos(u, s, c);
        A0 ru = rec(u);
        A0 r = polyval(p, ru)*s+polyval(q, ru)*c;
        auto r0 = if_zero_else(is_odd(P), cospi(P/2)*rec(sA0(P+1)));
        return  if_else(is_eqz(u), A0(r0), r);
      }
    };
  }
}


#endif
