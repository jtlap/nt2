//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D1_LOGSPACE_SUB_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D1_LOGSPACE_SUB_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/d1_logspace_sub.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d1_logspace_sub_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<unspecified_<A0>>)
                              (generic_<unspecified_<A1>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& x, const A1& y) const
    {
      A0 tmp =  exp(x);
      return rec(tmp - exp(y))*tmp;
    }
  };
} }


#endif
