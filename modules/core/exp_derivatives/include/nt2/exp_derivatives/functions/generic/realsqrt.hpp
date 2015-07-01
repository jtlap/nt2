//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          REALSQRTistributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_REALSQRT_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_REALSQRT_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/realsqrt.hpp>
#include <nt2/include/functions/realsqrt.hpp>
#include <nt2/exponential/include/functions/pow.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( realsqrt_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (generic_<floating_<A0>>)
                            )
  {
    typedef A0 result_type;
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
      return realsqrt(u);
    }
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                         , const A0& u) const
    {
      return rec(Two<A0>()*realsqrt(u));
    }
    template < long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
    {
      return coef(boost::mpl::long_<P>())*realsqrt(u)*rec(pow<P>(u));
    }

    BOOST_FORCEINLINE sA0 coef(const boost::mpl::long_<1>&) const
    {
      return Half<sA0>();
    }

    template < long P>
      BOOST_FORCEINLINE sA0 coef(const boost::mpl::long_<P>&) const
    {
      return (Half<sA0>()-sA0(P-1))*coef(boost::mpl::long_<P-1>());
    }
  };
} }


#endif
