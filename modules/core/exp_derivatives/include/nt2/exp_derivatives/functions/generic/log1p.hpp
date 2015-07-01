//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          LOG1Pistributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_LOG1PERIVATIVES_FUNCTIONS_GENERIC_LOG1P_LOG1P_HPP_INCLULOG1PELOG1P
#define NT2_EXP_LOG1PERIVATIVES_FUNCTIONS_GENERIC_LOG1P_LOG1P_HPP_INCLULOG1PELOG1P
#include <nt2/exp_derivatives/functions/log1p.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/exp_derivatives/functions/log.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
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
    BOOST_FORCEINLINE result_type operator()(const order&
                                              , const A0& u) const
    {
      return compute(order(), u);
    }
    private:
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<0>&
                                           , const A0& u) const
      {
        return log1p(u);
      }
      template < long P>
      BOOST_FORCEINLINE result_type compute(const boost::mpl::long_<P>&
                                           , const A0& u) const
      {
        return log(order(), oneplus(u));
      }
  };
} }


#endif
