//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRAI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRAI_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>

namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<shrai_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_integral<A0>
                      ,meta::is_scalar<A1>
                      ,meta::is_integral<A1>
                      > {};
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<shrai_,tag::simd_(tag::arithmetic_,tag::sse_),unsigned_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return shri(a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<shrai_,tag::simd_(tag::arithmetic_,tag::sse_),int64_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {

      A0 that = {shrai(a0[0], a1), shrai(a0[1], a1)}; 
      return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<shrai_,tag::simd_(tag::arithmetic_,tag::sse_),int32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0,signed>::type sint;
      sint const that = {_mm_srai_epi32(simd::native_cast<sint>(a0), a1)};
      return simd::native_cast<A0>(that);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<shrai_,tag::simd_(tag::arithmetic_,tag::sse_),int16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0,signed>::type sint;
      sint const that =  {_mm_srai_epi16(simd::native_cast<sint>(a0), a1)};
      return simd::native_cast<A0>(that);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<shrai_,tag::simd_(tag::arithmetic_,tag::sse_),int8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type result_type;
      typedef simd::native<typename meta::int16_t_<A0>::type,tag::sse_> gen_type;
      gen_type a0h, a0l;
      boost::fusion::tie(a0l, a0h) = split(a0);
      return simd::native_cast<A0>(group(shrai(a0l, a1),shrai(a0h, a1)));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
