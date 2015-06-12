//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_FAST_COSD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_FAST_COSD_HPP_INCLUDED
#include <nt2/trig_derivatives/functions/d_fast_cosd.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/fast_sind.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/deginrad.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_fast_cosd_, tag::cpu_
                            , (A0)
                            , (generic_<floating_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return -fast_sind(u)*Deginrad<A0>();
    }
  };
} }


#endif
