//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_ACSCH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_ACSCH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/acsch.hpp>
#include <nt2/include/functions/simd/acsch.hpp>
#include <nt2/include/functions/simd/asech.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( acsch_, tag::cpu_
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
        return acsch(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        result_type ru2 = rec(sqr(u));
        return  -ru2*rec(sqrt(oneplus(ru2)));
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        result_type u2 = sqr(u);
        result_type tmp0 = rec(oneplus(u2));
        return  oneplus(Two<sA0>()*u2)*tmp0*sqrt(tmp0)/u2;
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<3>
                                           , const A0& u) const
      {
        result_type x = rec(sqr(u));
        result_type sx = sqr(x);
        result_type opx =  oneplus(x);
        return -(sx*(sA0(2)*sx + sA0(5)*x + sA0(6)))/(sqr(opx)*sqrt(opx));
      }
     template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        long N = (P-2);
        result_type u2 = sqr(u);
        return -(compute( boost::mpl::long_<P-1>(), u)*(u2*sA0(3*N+2)+sA0(N+1))+
                 compute( boost::mpl::long_<P-2>(), u)*u*sA0(3*N+1)*sA0(N)+
                 compute( boost::mpl::long_<P-3>(), u)*(sA0(N*N*(N-1))))/(u*(oneplus(u2)));
      }
    };
  }
}


#endif

// d2 =

// 2/(x^3*(1/x^2 + 1)^(1/2)) - 1/(x^5*(1/x^2 + 1)^(3/2))


// d3 =

// 7/(x^6*(1/x^2 + 1)^(3/2)) - 6/(x^4*(1/x^2 + 1)^(1/2)) - 3/(x^8*(1/x^2 + 1)^(5/2))


// d4 =

// 24/(x^5*(1/x^2 + 1)^(1/2)) - 48/(x^7*(1/x^2 + 1)^(3/2)) + 45/(x^9*(1/x^2 + 1)^(5/2)) - 15/(x^11*(1/x^2 + 1)^(7/2))


// m =

// (1/x^2 + 1)^(1/2)


// zz =

// 1/x^2 + 1


// sd1 =

// -1/x^2


// sd2 =

// (2*x^2 + 1)/x^5


// sd3 =

// -(6*x^4 + 5*x^2 + 2)/x^8


// sd4 =

// (24*x^6 + 24*x^4 + 21*x^2 + 6)/x^11

