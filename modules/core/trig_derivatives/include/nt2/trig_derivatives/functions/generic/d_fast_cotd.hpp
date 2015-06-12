//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_FAST_COTD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_FAST_COTD_HPP_INCLUDED
#include <nt2/trig_derivatives/functions/d_fast_cotd.hpp>
#include <nt2/include/functions/d_fast_cot.hpp>
#include <nt2/include/functions/simd/inrad.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_fast_cotd_, tag::cpu_
                            , (A0)
                            , (generic_<floating_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return  inrad(d_fast_cot(inrad(u)));
    }
  };
} }


#endif
