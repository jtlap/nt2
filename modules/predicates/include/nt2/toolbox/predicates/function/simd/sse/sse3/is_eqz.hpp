//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE3_IS_EQZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE3_IS_EQZ_HPP_INCLUDED

#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/include/constants/digits.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_eqz_, tag::cpu_, (A0)
                            , ((simd_<arithmetic_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return eq(a0,Zero<A0>()); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::is_eqz_, tag::cpu_, (A0)
                            , ((simd_<int64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef simd::native <typename  meta::int32_t_<A0>::type, tag::sse_ > itype;
      typedef simd::native <typename  meta::float__<A0>::type , tag::sse_ > ftype;
      ftype tmp1
      = simd::native_cast<ftype>(eq(simd::native_cast<itype>(a0),Zero<itype>()));
      A0  l = simd::native_cast<A0>(_mm_moveldup_ps(tmp1));
      A0  h = simd::native_cast<A0>(_mm_movehdup_ps(tmp1));
      return b_and(l,h);
    }
  };
} }

#endif
