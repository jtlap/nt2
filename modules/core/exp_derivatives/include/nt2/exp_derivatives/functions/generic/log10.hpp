//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          LOG10istributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_LOG10_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_LOG10_HPP_INCLUDED
#include <nt2/exponential/functions/log10.hpp>
#include <nt2/exp_derivatives/functions/log10.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/constants/invlog_10.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( log10_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            , const A0& u) const
    {
      return log(order(), u)*Invlog_10<A0>();
    }
  };
} }


#endif
