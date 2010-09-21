//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/signnz.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for copysign

  /////////////////////////////////////////////////////////////////////////////
  // Compute copysign(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<copysign_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (real_,unsigned_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
	return b_or(abs(a0), bitofsign(a1));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,   unsigned_)
    {
      details::ignore_unused(a1); 
      return  a0; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
        return  signnz(a1)*abs(a0);
    }
  };
} }

      
#endif
