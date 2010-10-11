//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SIGNNZ_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SIGNNZ_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_positive.hpp>
#include <nt2/include/functions/seladd.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for signnz

  /////////////////////////////////////////////////////////////////////////////
  // Compute signnz(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<signnz_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//
    
    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (real_,unsigned,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,    real_)
    {
      return seladd(is_nan(a0), seladd(is_positive(a0), Mone<A0>(),Two<A0>()), a0);
    }
     NT2_FUNCTOR_CALL_EVAL_IF(1,    unsigned)
    {
      details::ignore_unused(a0); 
      return One<A0>(); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return is_ltz(a0)-is_gtz(a0); // here True is -1 False 0 !
    }
  };
} }

      
#endif
