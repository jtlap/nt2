//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_TRUE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_TRUE_HPP_INCLUDED

#include <nt2/sdk/simd/native_cast.hpp>

////////////////////////////////////////////////////////////////////////////////
// in SIMD, True is not !0 but ~0 whatever the type
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::true_, tag::cpu_, (A0)
                      , ((target_< simd_< arithmetic_<A0>,tag::altivec_> >))
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::true_( tag::target_<tag::simd_	<	tag::arithmetic_
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
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type that = { simd::native_cast<type>(vec_splat_u8(-1)) };
      return that;
    }
  };
} }

#endif

