//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_NEZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_NEZ_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/include/constants/digits.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_nez_, tag::cpu_, (A0)
                            , ((simd_<arithmetic_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return is_not_equal(a0,Zero<A0>()); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::is_nez_, tag::cpu_, (A0)
                            , ((simd_<double_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return is_not_equal(a0,Zero<A0>()); }
  };
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_nez_, tag::cpu_, (A0)
                            , ((simd_<type64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename meta::int32_t_<sctype >::type htype;
      typedef simd::native<htype,tag::sse_> type;
      type tmp1 = is_nez(simd::native_cast<type>(a0));
      const type tmp2 = {_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(2, 3, 0, 1))};

      return simd::native_cast<A0>(b_or(tmp1, tmp2));
    }
  };
} }

#endif
