//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_CSCD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_CSCD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cscd.hpp>
#include <nt2/trig_derivatives/functions/details/sec_kernel.hpp>
#include <nt2/include/functions/simd/cscd.hpp>
#include <nt2/include/functions/simd/cotd.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/deginrad.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( cscd_, tag::cpu_
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
        return cscd(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return -cscd(u)*cotd(u)*Deginrad<sA0>();
      }

      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        return  cscd(u)*oneplus(Two<A0>()*sqr(cotd(u)))*sqr(Deginrad<sA0>());
      }

      template<long P>
        BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                             , const A0& u) const
      {
        container::table<sA0> pol;
        details::sec_kernel<P, A0>::cscd_pl(pol);
        return cscd(u)*polyval(pol, cotd(u));
      }
    };
  }
}


#endif
