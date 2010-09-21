//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITOFSIGN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITOFSIGN_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for bitofsign

  /////////////////////////////////////////////////////////////////////////////
  // Compute bitofsign(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<bitofsign_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (real_,signed_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type result_type;
      return b_and(a0, Mzero<result_type>());
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     signed_)
    {
      static A0 const sm = (A0)Signmask<A0>();
      return b_and(a0, sm);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      details::ignore_unused(a0); 
      return Zero<A0>();
    }
  };
} }

      
#endif
