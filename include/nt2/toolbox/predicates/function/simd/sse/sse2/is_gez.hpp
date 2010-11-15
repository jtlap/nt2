//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_GEZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_GEZ_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
//#include <iostream>

namespace nt2 { namespace functors
{
  //  no special validate for is_gez


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_gez_,tag::simd_(tag::arithmetic_),unsigned_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0);
      return True<A0>();
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_gez_,tag::simd_(tag::arithmetic_),int64_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::int32_t_<A0>::type htype;
      typedef simd::native<htype,tag::sse_> type;
      const type tmp1 = is_gez(simd::native_cast<type>(a0));
      //      std::cout << "tmp1 " << tmp1 << std::endl; 
      const type tmp = { _mm_shuffle_epi32(tmp1, _MM_SHUFFLE(3, 3, 1, 1))}; //2, 2, 0, 0))};
//       std::cout << "tmp " << tmp << std::endl;
//       std::cout << "r   " <<  simd::native_cast<A0>(tmp) << std::endl;
      return  simd::native_cast<A0>(tmp);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_gez_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      return is_greater_equal(a0,Zero<A0>());
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
