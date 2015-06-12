//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_ASECD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_D_ASECD_HPP_INCLUDED
#include <nt2/trig_derivatives/functions/d_asecd.hpp>
#include <nt2/include/functions/d_asec.hpp>
#include <nt2/include/functions/simd/indeg.hpp>
namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_asecd_, tag::cpu_
                            , (A0)
                            , (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return indeg(d_asec(u));
    }
  };
} }


#endif
