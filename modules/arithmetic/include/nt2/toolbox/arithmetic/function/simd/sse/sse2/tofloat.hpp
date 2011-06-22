//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/make.hpp>

#include <nt2/toolbox/arithmetic/function/simd/common/tofloat.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::tofloat_, tag::cpu_, (A0)
                            , ((simd_<int32_<A0>,tag::sse_>))
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cvtepi32_ps(a0)};
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::tofloat_, tag::cpu_ , (A0)
                            , ((simd_<uint64_<A0>,tag::sse_>))
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type stype;
      return make<result_type>( static_cast<stype>(a0[0])
                              , static_cast<stype>(a0[1])
                              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::tofloat_, tag::cpu_ , (A0)
                            , ((simd_<uint32_<A0>,tag::sse_>))
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type stype;

      return make<result_type>( static_cast<stype>(a0[0])
                              , static_cast<stype>(a0[1])
                              , static_cast<stype>(a0[2])
                              , static_cast<stype>(a0[3])
                              );
      //TO DO
 //      typedef typename meta::scalar_of<A0>::type stype;
//       typedef typename meta::as_integer<A0,signed>::type sint_type;
//       //      static const sint_type hibitmask = integral_constant<sint_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const result_type offset = integral_constant<result_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const sint_type a00 = simd::native_cast<sint_type>(a0);
//       result_type v1 = {_mm_cvtepi32_ps(a00)};
//       result_type v2 = {_mm_cvtepi32_ps((b_andnot(a00, Signmask<sint_type>())))};
//       v2 = v2+offset;
//       return sel(is_gez(a00),v1,v2);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::tofloat_, tag::cpu_ , (A0)
                            , ((simd_<int64_<A0>,tag::sse_>))
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type sftype;
      if (maximum(abs(a0)) > Valmax<int32_t>())
      {
        return make<result_type>( static_cast<sftype>(a0[0])
                                , static_cast<sftype>(a0[1])
                                );
      }
      typedef typename meta::int32_t_<A0>::type htype;
      result_type v = { _mm_cvtepi32_pd(_mm_shuffle_epi32(a0,_MM_SHUFFLE(3,1,2,0)))};
      return v;
    }
  };
} }

#endif
