//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_AVX_NBTRUE_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_AVX_NBTRUE_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
tag::sse_
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/nbtrue.hpp>
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
      int32_t  r = _mm256_movemask_ps(isnez(a0));
      return   (r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3&1)+((r>>4)&1)+((r>>5)&1)+(r>>6&1)+(r>>7);
      //      return __builtin_popcount(_mm_movemask_ps(isnez(cast<type>(a0))));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      int32_t  r = _mm256_movemask_pd(isnez(a0));
      return   (r&1)+(r>>1&1)+((r>>2)&1)+(r>>3); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename meta::scalar_of<A0>::type sctype;		
      typedef typename simd::native<sctype, tag::sse_ >  svtype;	
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};			
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      return nbtrue(a00)+nbtrue(a01); 
    }
  };
} }

#endif