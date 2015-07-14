//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_ASINH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_ASINH_HPP_INCLUDED
#include <nt2/include/functions/simd/asinh.hpp>
#include <nt2/include/functions/simd/acosh.hpp>
#include <nt2/include/functions/simd/fms.hpp>
#include <nt2/include/functions/simd/fnma.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( asinh_, tag::cpu_
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
        return asinh(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return  rec(sqrt(oneplus(sqr(u))));
      }

      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        result_type tmp0 = rec(oneplus(sqr(u)));
        result_type tmp = sqrt(tmp0);
        return -u*tmp*tmp0;
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<3>
                                           , const A0& u) const
      {
        result_type u2 = sqr(u);
        result_type tmp0 = rec(oneplus(u2));
        result_type tmp = sqrt(tmp0);
        return minusone(Two<sA0>()*u2)*tmp*sqr(tmp0);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<4>
                                           , const A0& u) const
      {
        result_type u2 = sqr(u);
        result_type tmp0 = oneplus(u2);
        return -rec(sqrt(tmp0)*pow<3>(tmp0))*Three<sA0>()*u*fms(Two<sA0>(), u2, Three<sA0>());
      }
      template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        A0 opu2 = oneplus(sqr(u));
        A0 tmp = sqrt(opu2);
        return rec(tmp*pow<P-1>(opu2))*K( boost::mpl::long_<P>(), u, opu2);
      }

      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<0>
                                     , const A0&
                                     , const A0& ) const
      {
        return Zero<result_type>(); ;
      }
      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<1>
                                     , const A0&
                                     , const A0& ) const
      {
        return One<result_type>();
      }
      template<long P>
      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<P>
                                     , const A0& x, const A0& opx2) const
      {
        return fnma(opx2
                   , sqr(sA0(P-2))*K(boost::mpl::long_<P-2>(), x, opx2)
                   , sA0(2*P-3)*x*K(boost::mpl::long_<P-1>(), x, opx2));
      }
   };
  }
}


#endif
