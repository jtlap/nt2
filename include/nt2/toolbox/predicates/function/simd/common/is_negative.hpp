//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_NEGATIVE_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_NEGATIVE_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/shrai.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for is_negative

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_negative(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<is_negative_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (real_,unsigned_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       unsigned_)
    {
      details::ignore_unused(a0);
      return False<A0>();
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      return is_ltz(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      typedef typename meta::as_integer<A0, signed>::type type;
      const int32_t nb =  sizeof(typename meta::scalar_of <A0>::type)*8-1; 
      return simd::native_cast<A0>(shrai(simd::native_cast<type>(a0), nb));
      //     return simd::native_cast<A0>(is_nez(simd::native_cast<type>(b_and(a0, Signmask<A0>())))); 
    }
  };
} }

      
#endif
