//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ASEC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ASEC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/asec.hpp>
#include <nt2/include/functions/simd/asec.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( asec_, tag::cpu_
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
        return asec(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        result_type ru2 = rec(sqr(u));
        return  -ru2*rec(sqrt((oneminus(ru2))));
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        result_type ru2 = rec(sqr(u));
        result_type omru2 = oneminus(ru2);
        result_type fac = oneplus(omru2)/(omru2*u);
        return  ru2*rec(sqrt((omru2)))*fac;
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<3>
                                           , const A0& u) const
      {
        result_type x = rec(sqr(u));
        return -(sqr(x)*(sA0(2)*sqr(x) - sA0(5)*x + sA0(6)))/(sqr((1 - x))*sqrt(1-x));
      }
      template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        long N = (P-2);
        result_type u2 = sqr(u);
        return (compute( boost::mpl::long_<P-1>(), u)*(u2*sA0(3*N+2)-sA0(N+1))+
                compute( boost::mpl::long_<P-2>(), u)*(u*sA0(3*N+1)*sA0(N))+
                compute( boost::mpl::long_<P-3>(), u)*(sA0(N*(N-1))*(sA0(N-2)*u+sA0(2))))/(u*(minusone(u2)));
      }



   };
  }
}


#endif
