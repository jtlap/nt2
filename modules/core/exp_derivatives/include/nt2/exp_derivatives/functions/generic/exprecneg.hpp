//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_EXPRECNEG_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_EXPRECNEG_HPP_INCLUDED
#include <nt2/exponential/functions/exprecneg.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( exprecneg_, tag::cpu_
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
        return exprecneg(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<1>
                                           , const A0& u) const
      {
        return exprecneg(u)/sqr(u);
      }
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<2>
                                           , const A0& u) const
      {
        return exprecneg(u)*oneminus(u+u)/sqr(sqr(u));
      }

      template < long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u) const
      {
        return exprecneg(u)*pl<order>(rec(u));
      }

      BOOST_FORCEINLINE sA0 pl(const boost::mpl::long_<0>&, const result_type) const
      {
        return sA0(1);
      }

      BOOST_FORCEINLINE sA0 pl(const boost::mpl::long_<1>&, const result_type ru) const
      {
        return sqr(ru);
      }

      template < long P>
      BOOST_FORCEINLINE sA0 pl(const boost::mpl::long_<P>&, const result_type ru) const
      {
        return ru*fma((sA0(2*P-2)-ru), pl(boost::mpl::long_<P-1>(), ru), sA0((P-1)*P)*pl(boost::mpl::long_<P-2>(), ru));
      }
    };
  }
}


#endif
