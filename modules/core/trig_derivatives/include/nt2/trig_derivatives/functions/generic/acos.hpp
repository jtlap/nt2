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
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>

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
        result_type tmp = rec(sqrt(oneminus(sqr(u))));
        return -u*tmp*sqr(tmp);
      }
      template<long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        A0 tmp0 = oneminus(sqr(u));
        A0 tmp = sqrt(tmp0);
        return -rec(tmp*pow<P-1>(tmp0))*K( boost::mpl::long_<P>(), tmp0);
      }

      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<0>
                                           , const A0& ) const
      {
        return Zero<result_type>(); ;
      }
      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<1>
                                           , const A0& x) const
      {
        return x;
      }
      template<long P>
      BOOST_FORCEINLINE result_type K(const boost::mpl::long_<P>
                                           , const A0& x) const
      {
        return sA0(2*P-3)*K(boost::mpl::long_<P-1>(), x)-sqr(sA0(P-2))*K(boost::mpl::long_<P-2>(), x);
    }



   };
  }
}


#endif
