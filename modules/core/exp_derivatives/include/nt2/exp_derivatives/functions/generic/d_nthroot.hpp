//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D_NTHROOT_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_D_NTHROOT_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/d_nthroot.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_nthroot_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<unspecified_<A0>>)
                              (generic_<integer_<A1>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u, const A1& n) const
    {
      A0 rn = rec(tofloat(n));
      return pow(u, minusone(rn))*rn;
    }
  };
} }


#endif
