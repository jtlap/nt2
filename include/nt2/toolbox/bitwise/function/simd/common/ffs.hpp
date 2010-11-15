//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_FFS_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_FFS_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/firstbitset.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for ffs

  /////////////////////////////////////////////////////////////////////////////
  // Compute ffs(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::simd_(tag::arithmetic_),types8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef typename simd::native<uint64_t,ext> ltype;
      rtype v = firstbitset(a0);
      return b_and(is_nez(v), b_or(b_or((-( is_nez(b_and(v, integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
		       ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
		  ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))+One<rtype>()); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::simd_(tag::arithmetic_),types16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef typename simd::native<uint64_t,ext> ltype;
      rtype v = firstbitset(a0);
      return  b_and(is_nez(v), b_or(b_or(b_or((-( is_nez(b_and(v, integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
			     ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
			,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))
				    ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xFF00FF00FF00FF00ll>()))), 3))+One<rtype>()); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::simd_(tag::arithmetic_),types32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext; 
      typedef typename simd::native<uint64_t, ext> ltype;
      rtype v = firstbitset(a0);
      return  b_and(is_nez(v), b_or(b_or(b_or(b_or((-( is_nez(b_and(v, integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
				  ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
			     ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))
			,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xFF00FF00FF00FF00ll>()))), 3))
		   ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xFFFF0000FFFF0000ll>()))), 4))+One<rtype>()); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::simd_(tag::arithmetic_),types64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      return  simd::native_cast<rtype>(map(functor<ffs_>(), simd::native_cast<rtype>(a0)));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
