//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_PUT_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_PUT_FIRST_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>

namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<put_first_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
     template<class Sig> struct result;

     template<class This,class A0,class A1>
     struct result<This(A0,A1)> :
       boost::mpl::and_<meta::is_scalar<A1>,
			meta::is_integral<A1>
       > {};
   };
  template<class Extension,class Info>
  struct call<put_first_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};


    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (5, (types8_,types16_,types32_,double,types64_))
     )

    NT2_FUNCTOR_CALL_EVAL_IF(2,    types8_)
    {
      typedef simd::native<typename meta::double_<A0>::type,tag::sse_>   rtype; 
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64; 
      if(a1 > 7)
	{
	  A0 t = { _mm_srli_si128(simd::native_cast<type64>(a0), 8 )};
	  return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-8) << 3));
	}
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 3));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,    types16_)
    {
      typedef simd::native<typename meta::double_<A0>::type,tag::sse_>   rtype; 
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
      if(a1 > 3)
	{
	  A0 t = { _mm_srli_si128(simd::native_cast<type64>(a0), 8 )};
	  return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-4) << 4));
	}
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 4));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,    types32_)
    {
      typedef simd::native<typename meta::double_<A0>::type,tag::sse_>   rtype; 
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
      if(a1 > 1)
	{
	  A0 t = { simd::native_cast<A0>(_mm_srli_si128(simd::native_cast<type64>(a0), 8 ))};
	  return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-2) << 5));
	}
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 5));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,    double)
    {
      if(a1)
	{
	  A0 that = { _mm_unpackhi_pd(a0,a0)};
	  return that;
	}
      return a0;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,    types64_)
    {
      typedef typename meta::as_real<A0>::type rtype;
      if(a1)
	{
	  return simd::native_cast<A0>(_mm_unpackhi_pd(simd::native_cast<rtype>(a0),simd::native_cast<rtype>(a0)));
	}
      return a0;
    }

  };
} }

#endif
