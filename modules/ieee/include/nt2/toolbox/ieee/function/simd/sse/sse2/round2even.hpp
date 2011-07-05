//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSE2_ROUND2EVEN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSE2_ROUND2EVEN_HPP_INCLUDED

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/constants/properties.hpp>
#include <nt2/include/functions/select.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::round2even_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return a0; }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::round2even_, tag::cpu_, (A0)(X)
                            , ((simd_<real_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      const result_type v   = nt2::abs(a0);
      const result_type t2n = Two2nmb<A0>();
      const result_type d0  = (v+t2n);
      const result_type d   = (d0-t2n);
      const result_type d1  = sel(lt(v,t2n),d,v);
      return (d1^bitofsign(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::round2even_, tag::cpu_, (A0)(X)
                            , ((simd_<float_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = {_mm_cvttps_epi32(a0)}; 
      return tofloat(that);
    }
  };
  
} }

#endif
