//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D_EXP2_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D_EXP2_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/d_exp2.hpp>
#include <nt2/include/functions/simd/exp2.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/log_10.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_exp2_, tag::cpu_
                            , (A0)
                            , (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return exp2(u)*Log_2<A0>();
    }
  };
} }


#endif
