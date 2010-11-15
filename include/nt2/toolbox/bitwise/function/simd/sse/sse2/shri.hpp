//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRI_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <iostream>
#include <nt2/sdk/details/type_id.hpp>
namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<shri_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_scalar<A1>
      ,meta::is_integral<A1>
      > {};
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<shri_,tag::simd_(tag::arithmetic_),types64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename meta::as_integer<A0>::type sint;
        sint const that ={ _mm_srli_epi64(simd::native_cast<sint>(a0),a1)};
        return simd::native_cast<A0>(that);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<shri_,tag::simd_(tag::arithmetic_),types32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename meta::as_integer<A0>::type sint;
        sint const that = { _mm_srli_epi32(simd::native_cast<sint>(a0), a1)};
        return simd::native_cast<A0>(that);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<shri_,tag::simd_(tag::arithmetic_),types16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = {_mm_srli_epi16(a0, a1)};
      return that;
    } 
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<shri_,tag::simd_(tag::arithmetic_),types8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename NT2_CALL_RETURN_TYPE(2)::type result_type;
	typedef simd::native<typename meta::int32_t_<A0>::type,tag::sse_> gen_type;
        result_type const Mask1 =  simd::native_cast<result_type>(integral_constant<gen_type, 0x00ff00ff>());
	result_type const Mask2 =  simd::native_cast<result_type>(integral_constant<gen_type, 0xff00ff00>());
	result_type tmp  = b_and(a0, Mask1);
        result_type tmp1 = {_mm_srli_epi16(tmp, a1)};
	tmp1 = b_and(tmp1, Mask1);
        tmp = b_and(a0, Mask2);
	result_type tmp3 = {_mm_srli_epi16(tmp, a1)}; 
        result_type tmp2 = b_and(tmp3, Mask2);
        return tmp1 | tmp2;
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
