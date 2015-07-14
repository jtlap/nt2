//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_TANH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_TANH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/tanh.hpp>
#include <nt2/hyp_derivatives/functions/details/dtanh_kernel.hpp>
#include <nt2/include/functions/simd/tanh.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>


namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( tanh_, tag::cpu_
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
        return nt2::tanh(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return oneminus(sqr(tanh(u)));;
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        result_type x = tanh(u);
        return  -oneminus(sqr(x))*x*Two<result_type>();
      }

      template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        container::table<sA0> pol;
        details::dtanh_kernel<P, A0>::tanh_pl(pol);
        return polyval(pol, nt2::tanh(u));
      }
    };
  }
}


#endif
