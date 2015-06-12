//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_SECANT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_SECANT_HPP_INCLUDED
#include <nt2/trig_derivatives/functions/d_secant.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/secant.hpp>
#include <nt2/include/functions/simd/tangent.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT_G  ( nt2::tag::d_secant_<mode>, tag::cpu_
                              , (A0)(mode)
                              , (generic_<unspecified_<A0>>)
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return  tangent<mode>(u)*secant<mode>(u);
    }
  };
} }


#endif
