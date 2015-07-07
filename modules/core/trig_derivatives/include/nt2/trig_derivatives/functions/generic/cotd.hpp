//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_COTD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_COTD_HPP_INCLUDED
#include <nt2/include/functions/simd/cotd.hpp>
#include <nt2/include/functions/simd/cot.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/constants/deginrad.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( cotd_, tag::cpu_
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
        return cotd(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return -oneplus(sqr(cotd(u)))*Deginrad<result_type>();
      }

      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        result_type x = cotd(u);
        return  oneplus(sqr(x))*x*Two<result_type>()*sqr(Deginrad<result_type>());
      }

      template<long P>
        BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                             , const A0& u) const
      {
        container::table<sA0> pol;
        details::tan_kernel<P, A0>::cotd_pl(pol);
        return polyval(pol, cotd(u));
      }
    };
  }
}


#endif
