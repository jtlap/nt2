//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_SINCPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_SINCPI_HPP_INCLUDED
#include <nt2/trig_derivatives/functions/d_sincpi.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/fms.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/simd/sincospi.hpp>
#include <nt2/include/constants/pi.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_sincpi_, tag::cpu_
                            , (A0)
                            , (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      A0 s, c;
      sincospi(u, s, c);
      A0 piu =  Pi<A0>()*u;
      return  Pi<A0>()*if_zero_else(is_eqz(u), fms(c,  piu, s)/sqr(piu));
    }
  };
} }


#endif
