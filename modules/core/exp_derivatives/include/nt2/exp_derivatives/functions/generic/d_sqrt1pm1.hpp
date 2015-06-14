//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D_SQRT1PM1_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D_SQRT1PM1_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/d_sqrt1pm1.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/constants/two.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_sqrt1pm1_, tag::cpu_
                            , (A0)
                            , (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return rec(Two<A0>()*sqrt(oneplus(u)));
    }
  };
} }


#endif
