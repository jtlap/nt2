//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_LOG1P_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_LOG1P_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/log1p.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( log1p_, tag::cpu_
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
      return compute(order(), u, boost::mpl::long_<order::value % 2>());
    }
  private:
    BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>&
                                         , const A0& u
                                         , const boost::mpl::long_<0>&) const
    {
      return log1p(u);
    }
    template < long P, long Q>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>&
                                           , const A0& u
                                           , const boost::mpl::long_<Q>&) const
    {
      return compensated_fact(boost::mpl::long_<P>(), rec(oneplus(u)));
    }
    template < long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
                                           , const A0& u
                                           , const boost::mpl::long_<0>&) const
    {
      return -compensated_fact(boost::mpl::long_<P>(), rec(oneplus(u)));
    }


    BOOST_FORCEINLINE result_type compensated_fact(const boost::mpl::long_<0>
                                                  , const A0& ) const
    {
      return One<result_type>();
    }
    BOOST_FORCEINLINE result_type compensated_fact(const boost::mpl::long_<1>
                                                  , const A0& ru) const
    {
      return ru;
    }
    BOOST_FORCEINLINE result_type compensated_fact(const boost::mpl::long_<2>
                                                  , const A0& ru) const
    {
      return sqr(ru);
    }
    template < long P>
      BOOST_FORCEINLINE result_type compensated_fact(const boost::mpl::long_<P>
                                                    , const A0& ru) const
    {
      return sA0(P-1)*ru*compensated_fact(boost::mpl::long_<P-1>(), ru);
    }

//       template < long P>
//       BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>
//                                            , const A0& u) const
//       {
//         return log(order(), oneplus(u));
//       }
  };
} }


#endif
