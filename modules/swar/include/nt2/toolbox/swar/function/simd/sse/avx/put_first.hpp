//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_PUT_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_PUT_FIRST_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/templatize.hpp>

#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/details/simd/sse/sse4_1/put_first.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0),
                            ((simd_<arithmetic_<A0>,tag::avx_>))
                            ((simd_<arithmetic_<A0>,tag::avx_>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::arithmetic_, tag::avx_),
                              tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)>  {typedef A0 type; };

    NT2_FUNCTOR_CALL(2){return a0; }

  };
} }

#endif
// modified by jt the 05/01/2011