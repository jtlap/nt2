//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSSE3_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSSE3_SUM_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/first.hpp>
#include <nt2/include/functions/second.hpp>
#include <boost/fusion/include/fold.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for sum


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sum_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename boost::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      A0 tmp = {_mm_hadd_ps(a0, Zero<A0>())};
      return  first(simd::native_cast<A0>(_mm_hadd_ps(tmp, Zero<A0>())));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sum_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename boost::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return first(simd::native_cast<A0>(_mm_hadd_pd( a0, Zero<A0>())));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sum_,tag::simd_(tag::arithmetic_,tag::sse_),int8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename boost::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
	return boost::fusion::fold(a0,0,functor<plus_>());
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sum_,tag::simd_(tag::arithmetic_,tag::sse_),int16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename boost::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      A0 tmp = {_mm_hadd_epi16(a0, a0)};
      A0 tmp1 = {_mm_hadd_epi16(tmp, tmp)};
      return  first(simd::native_cast<A0>(_mm_hadd_epi16(tmp1, tmp1)));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sum_,tag::simd_(tag::arithmetic_,tag::sse_),int32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename boost::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      A0 tmp = {_mm_hadd_epi32(a0, a0)};
      return  first(simd::native_cast<A0>(_mm_hadd_epi32(tmp, tmp)));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sum_,tag::simd_(tag::arithmetic_,tag::sse_),int64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename boost::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return first(a0)+second(a0);
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
