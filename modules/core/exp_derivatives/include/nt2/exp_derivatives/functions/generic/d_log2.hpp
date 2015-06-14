//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LOG_DERIVATIVES_FUNCTIONS_GENERIC_D_LOG2_HPP_INCLUDED
#define NT2_LOG_DERIVATIVES_FUNCTIONS_GENERIC_D_LOG2_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/d_log2.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/invlog_2.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_log2_, tag::cpu_
                            , (A0)
                            , (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return rec(u)*Invlog_2<A0>();
    }
  };
} }


#endif
