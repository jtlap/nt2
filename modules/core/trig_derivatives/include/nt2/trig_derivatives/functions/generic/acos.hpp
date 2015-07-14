//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ACOS_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ACOS_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acos.hpp>
#include <nt2/include/functions/simd/acos.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( acos_, tag::cpu_
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
        return acos(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return  -rec(sqrt(oneminus(sqr(u))));
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        result_type tmp0 = rec(oneminus(sqr(u)));
        result_type tmp = sqrt(tmp0);
        return -u*tmp*tmp0;
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<3>
                                           , const A0& u) const
      {
        result_type u2 = sqr(u);
        result_type tmp0 = rec(oneminus(u2));
        result_type tmp = sqrt(tmp0);
        return -oneplus(Two<sA0>()*u2)*tmp*sqr(tmp0);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<4>
                                           , const A0& u) const
      {
        result_type u2 = sqr(u);
        result_type tmp0 = oneminus(u2);
        return -rec(sqrt(tmp0)*pow<3>(tmp0))*Three<sA0>()*u*fma(Two<sA0>(), u2, Three<sA0>());
      }
      template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        A0 omu2 = oneminus(sqr(u));
        A0 sqomu2 = sqrt(omu2);
        return -rec(sqomu2*pow<P-1>(omu2))*K( boost::mpl::long_<P>(), u, omu2);
      }

      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<0>
                                           , const A0&
                                           , const A0&) const
      {
        return Zero<result_type>(); ;
      }
      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<1>
                                           , const A0&
                                           , const A0&) const
      {
        return One<result_type>();
      }
      template<long P>
      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<P>
                                           , const A0& x
                                           , const A0& omx2) const
      {
        return fma(sA0(2*P-3)*x, K(boost::mpl::long_<P-1>(), x, omx2), omx2*sqr(sA0(P-2))*K(boost::mpl::long_<P-2>(), x, omx2));
    }



   };
  }
}


#endif
