//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for nbtrue

  template<class Extension,class Info>
  struct call<nbtrue_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    typedef int32_t result_type; 

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
      typedef typename meta::as_real<A0>::type type; 
      int32_t  r = _mm_movemask_ps(is_nez(a0));
      return   (r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3);
      //      return __builtin_popcount(_mm_movemask_ps(isnez(cast<type>(a0))));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      int32_t  r = _mm_movemask_pd(is_nez(a0));
      return   (r&1)+(r>>1); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename simd::native<typename meta::int8_t_<A0>::type,tag::sse_> i8type;
      i8type tmp = {is_nez(a0)};
      return __builtin_popcount(_mm_movemask_epi8(tmp))*meta::cardinal_of<A0>::value >> 4;
    }
  };
} }

#endif
