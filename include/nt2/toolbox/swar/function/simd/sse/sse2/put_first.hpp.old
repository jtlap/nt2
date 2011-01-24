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

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<put_first_,tag::simd_(tag::arithmetic_,tag::sse_),types8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
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
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<put_first_,tag::simd_(tag::arithmetic_,tag::sse_),types16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
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
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<put_first_,tag::simd_(tag::arithmetic_,tag::sse_),types32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
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
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<put_first_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      if(a1)
	{
	  A0 that = { _mm_unpackhi_pd(a0,a0)};
	  return that;
	}
      return a0;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<put_first_,tag::simd_(tag::arithmetic_,tag::sse_),types64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
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
/// Revised by jt the 15/11/2010
