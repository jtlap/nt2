//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSE2_ILOGB_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSE2_ILOGB_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/predecessor.hpp>
#include <nt2/include/functions/dist.hpp>
#include <iostream>

#define MKN(N) simd::native_cast<vtype##N>

namespace nt2 { namespace functors
{
  //  no special validate for ilogb


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::simd_(tag::arithmetic_,tag::sse_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
// 	typedef typename meta::scalar_of<A0>::type sA0; 
//         typedef typename meta::is_signed<sA0>::type sgn; 
	typedef typename meta::as_integer<A0>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      return exponent(a0);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is signed_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::simd_(tag::arithmetic_,tag::sse_),signed_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
// 	typedef typename meta::scalar_of<A0>::type sA0; 
//         typedef typename meta::is_signed<sA0>::type sgn; 
	typedef typename meta::as_integer<A0>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type vtype; 
      static const A0 z = Zero<A0>();
      vtype tmp = ilogb(simd::native_cast<vtype>(a0)); 
      return seladd(is_gtz(a0), z, simd::native_cast<A0>(tmp)); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::simd_(tag::arithmetic_,tag::sse_),uint8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
// 	typedef typename meta::scalar_of<A0>::type sA0; 
//         typedef typename meta::is_signed<sA0>::type sgn; 
	typedef typename meta::as_integer<A0>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef A0 vtype8; 
      static const vtype8& o = One<vtype8>();
      static const vtype8 mask =  integral_constant<vtype8, 0x7f>();
      typedef typename A0::extension_type cat; 
      typedef simd::native<uint16_t, cat> type; 
      vtype8 n = a0;
      vtype8 i = o;
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o); 
      return i-o;      
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::simd_(tag::arithmetic_,tag::sse_),uint16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
// 	typedef typename meta::scalar_of<A0>::type sA0; 
//         typedef typename meta::is_signed<sA0>::type sgn; 
	typedef typename meta::as_integer<A0>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef A0 vtype16; 
      typedef typename A0::extension_type cat; 
      typedef simd::native<uint8_t, cat>  vtype8;
      static const vtype8& z = Zero<vtype8>();
      static const vtype8& o = One<vtype8>();
      static const vtype16 mask =  integral_constant<vtype16, 0x7f7f > (); 
      vtype8 i = select(is_eqz(MKN(8)(a0)), z, o);
      //      vtype8 i = sb2b(is_nez((vtype8)a0)); 
      vtype8 n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(a0, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      
      static const vtype16 mask1 = integral_constant<vtype16, 0x00ff>();
      static const vtype16 mask2 = integral_constant<vtype16, 0xff00>();
      static const vtype16 huit  = integral_constant<vtype16, 8u>();
      
      vtype16 yy = b_and(MKN(16)(i), mask2);
      vtype16 zz = b_and(MKN(16)(i), mask1); 
      vtype16 xx = sel(is_nez(yy), MKN(16)(_mm_srli_epi16(yy, 8))+huit, zz);
      return MKN(16)(is_nez(MKN(8)(xx))&(MKN(8)(xx)-o)); 
				    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::simd_(tag::arithmetic_,tag::sse_),uint32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
// 	typedef typename meta::scalar_of<A0>::type sA0; 
//         typedef typename meta::is_signed<sA0>::type sgn; 
	typedef typename meta::as_integer<A0>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename A0::extension_type cat; 
      typedef A0 vtype32; 
      typedef simd::native<uint8_t, cat>  vtype8;
      static const vtype8& z = Zero<vtype8>();
      static const vtype8& o = One<vtype8>();
      static const vtype32 mask =  integral_constant<vtype32, 0x7f7f7f7f>(); 
      //      vtype8 i = boolean(is_nez((vtype8)a0));
      vtype8 i = select(is_eqz(MKN(8)(a0)), z, o);
      vtype8 n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(a0, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      static const vtype32 mask1 = integral_constant<vtype32,0x000000ff>();
      static const vtype32 mask2 = integral_constant<vtype32,0x0000ff00>();
      static const vtype32 mask3 = integral_constant<vtype32,0x00ff0000>();
      static const vtype32 mask4 = integral_constant<vtype32,0xff000000>(); 
      static const vtype32 huit  = integral_constant<vtype32,8>();
      static const vtype32 seize = integral_constant<vtype32,16u>();
      static const vtype32 v4    = integral_constant<vtype32,24u>(); 
      
      vtype32 yy = b_and(MKN(32)(i), mask4);
      vtype32 zz = b_and(MKN(32)(i), mask3);
      vtype32 tt = b_and(MKN(32)(i), mask2);
      vtype32 uu = b_and(MKN(32)(i), mask1); 
      vtype32 xx = sel(is_nez(yy), MKN(32)(_mm_srli_epi32(yy,24))+v4,
		     sel(is_nez(zz), MKN(32)(_mm_srli_epi32(zz,16))+seize,
			 sel(is_nez(tt), MKN(32)(_mm_srli_epi32(tt,8))+huit,
			     uu))); 
      return MKN(32)(is_nez(MKN(8)(xx))&(MKN(8)(xx)-o)); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint64_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::simd_(tag::arithmetic_,tag::sse_),uint64_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
// 	typedef typename meta::scalar_of<A0>::type sA0; 
//         typedef typename meta::is_signed<sA0>::type sgn; 
	typedef typename meta::as_integer<A0>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename A0::extension_type cat; 
      typedef simd::native<uint64_t, cat> vtype64; 
      return simd::native_cast<vtype64>(exponent(tofloat(a0)));
    }
  };

} }

#endif
#undef MKN
/// Revised by jt the 15/11/2010
