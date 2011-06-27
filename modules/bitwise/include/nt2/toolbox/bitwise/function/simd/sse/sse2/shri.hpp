//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRI_HPP_INCLUDED

#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/constants/digits.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::shri_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<type8_<A0>,tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef simd::native<typename meta::int32_t_<A0>::type,tag::sse_> gen_type;
      result_type const Mask1 =  simd::native_cast<result_type>(integral_constant<gen_type, 0x00ff00ff>());
      result_type const Mask2 =  simd::native_cast<result_type>(integral_constant<gen_type, 0xff00ff00>());
      result_type tmp  = b_and(a0, Mask1);
      result_type tmp1 = {_mm_srli_epi16(tmp, a1)};
      tmp1 = b_and(tmp1, Mask1);
      tmp = b_and(a0, Mask2);
      result_type tmp3 = {_mm_srli_epi16(tmp, a1)};
      return tmp1 | b_and(tmp3, Mask2);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(tag::shri_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<type32_<A0>,tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0>::type sint;
      sint const that = { _mm_srli_epi32(simd::native_cast<sint>(a0), a1)};
      return simd::native_cast<A0>(that);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::shri_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<type64_<A0>,tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0>::type sint;
      sint const that ={ _mm_srli_epi64(simd::native_cast<sint>(a0),a1)};
      return simd::native_cast<result_type>(that);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::shri_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<type16_<A0>,tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = {_mm_srli_epi16(a0, a1)};
      return that;
    }
  };
} }

#endif
