//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_CSCH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_CSCH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/csch.hpp>
#include <nt2/hyp_derivatives/functions/details/sech_kernel.hpp>
#include <nt2/include/functions/simd/csch.hpp>
#include <nt2/include/functions/simd/coth.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( csch_, tag::cpu_
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
        return csch(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return -csch(u)*coth(u);
      }

      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        return  -csch(u)*oneminus(Two<A0>()*sqr(coth(u)));
      }

      template<long P>
        BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                             , const A0& u) const
      {
        container::table<sA0> pol;
        details::sech_kernel<P, A0>::csch_pl(pol);
        return csch(u)*polyval(pol, coth(u));
      }
    };
  }
}


#endif
