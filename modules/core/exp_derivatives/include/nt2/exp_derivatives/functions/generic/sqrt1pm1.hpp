//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          SQRT1PM1istributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_SQRT1PM1_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_SQRT1PM1_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/sqrt1pm1.hpp>
#include <nt2/include/functions/sqrt1pm1.hpp>
#include <nt2/exponential/include/functions/pow.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/constants/two.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( sqrt1pm1_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (generic_<unspecified_<A0>>)
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
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>&
                                         , const A0& u) const
    {
      return sqrt1pm1(u);
    }
    template < long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>&
                                           , const A0& u) const
    {
      using nt2::sqrt;
      A0 up1 = oneplus(u);
      return coef(boost::mpl::long_<P>())*sqrt(up1)*rec(pow<P>(up1));
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
