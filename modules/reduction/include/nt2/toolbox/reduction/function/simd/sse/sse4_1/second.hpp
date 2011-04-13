/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE4_1_SECOND_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE4_1_SECOND_HPP_INCLUDED

#include <nt2/toolbox/reduction/function/simd/sse/ssse3/second.hpp>

#ifdef NT2_ARCH_X86_64
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::second_, tag::sse4_1_,
                         (A0),
                         ((simd_<ints64_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::second_(tag::simd_<tag::ints64_, tag::sse_> ),
              tag::sse4_1_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};


    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      type z = {_mm_extract_epi64(a0, 1)};
      return z;
    }
  };
} }
#endif

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of second.hpp
// /////////////////////////////////////////////////////////////////////////////
