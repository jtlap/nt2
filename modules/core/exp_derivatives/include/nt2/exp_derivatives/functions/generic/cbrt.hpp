//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_CBRT_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_CBRT_HPP_INCLUDED
#include <nt2/include/functions/simd/cbrt.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/pow.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( cbrt_, tag::cpu_
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
        return cbrt(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return rec(Three<A0>()*sqr(cbrt(u)));
      }
      template < long P>
        BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                             , const A0& u) const
      {
        return coef(boost::mpl::long_<P>())*cbrt(u)*rec(pow<P>(u));
      }

      BOOST_FORCEINLINE sA0 coef(const boost::mpl::long_<1>&) const
      {
        return Third<sA0>();
      }

      template < long P>
        BOOST_FORCEINLINE sA0 coef(const boost::mpl::long_<P>&) const
      {
        return (Third<sA0>()-sA0(P-1))*coef(boost::mpl::long_<P-1>());
      }
    };
  }
}


#endif
