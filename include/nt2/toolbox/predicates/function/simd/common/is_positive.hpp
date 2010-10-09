//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_POSITIVE_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_POSITIVE_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_gez.hpp>
//#include <iostream>

namespace nt2 { namespace functors
{
  //  no special validate for is_positive

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_positive(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<is_positive_,
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

    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      return is_gez(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      typedef typename meta::as_integer<A0, signed>::type type;
//       std::cout << "simd::native_cast<type>(a0) "<< simd::native_cast<type>(a0) << std::endl;
//       std::cout << "is_gez ?                    "<< is_gez(simd::native_cast<type>(a0)) << std::endl;
      return simd::native_cast<A0>(is_gez(simd::native_cast<type>(a0)));
    }
  };
} }

      
#endif
