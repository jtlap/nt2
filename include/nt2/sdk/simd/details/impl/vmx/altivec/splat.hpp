/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_SPLAT_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Registers dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)
                      , (fundamental_<A0>)
                        ((target_< simd_< arithmetic_<A1>, tag::altivec_ > >))
                      )

////////////////////////////////////////////////////////////////////////////////
// Implements dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::simd_	<	tag::arithmetic_
																											,	tag::altivec_
																											> 
																					>
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      typename type::extraction_type v;
      v.s[0] = a0;
      type that = {vec_splat(v.v, 0)};
      return that;
    }
  };
} }

#endif
