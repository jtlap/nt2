//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D2_LOGSPACE_SUB_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D2_LOGSPACE_SUB_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/d_logspace_sub.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d2_logspace_sub_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<unspecified_<A0>>)
                              (generic_<unspecified_<A1>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& x, const A0& y) const
    {
      A0 tmp =  -exp(y);
      return rec(tmp + exp(x))*tmp;
    }
  };
} }


#endif
