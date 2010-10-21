//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_NOT_FINITE_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_NOT_FINITE_HPP_INCLUDED
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_nan.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for is_not_finite

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_not_finite(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<is_not_finite_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      return is_nan(a0-a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      details::ignore_unused(a0); 
      return False<A0>();
    }
  };
} }

      
#endif
