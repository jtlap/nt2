//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_SQRT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_SQRT_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/toint.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for sqrt


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = { _mm256_sqrt_ps(a0)}; return that; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = { _mm256_sqrt_pd(a0)}; return that; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint64_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),uint64_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      return simd::native_cast<A0>(toint(sqrt(tofloat(a0))));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),uint32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 const na = isnez(a0);
      A0 const z1 = add(shri(a0, 6),    integral_constant<A0,16>());
      A0 const z2 = add(shri(a0,10),   integral_constant<A0,256>());
      A0 const z3 = add(shri(a0,13),  integral_constant<A0,2048>());
      A0 const z4 = add(shri(a0,16), integral_constant<A0,16384>());
      static A0 const one = One<A0>();
      
      A0 n  = select( isgt(a0, integral_constant<A0,177155824>())
		      , z4
		      , select( isgt(a0, integral_constant<A0,4084387>())
				, z3
				, select( isgt(a0, integral_constant<A0,31679>())
					  , z2
					  , z1
					  )
				)
		      );
      
      A0 ok =  isgtz(n);
      n = select(ok, n, one);
      A0 n1 = select(ok, shri(n+a0/n, 1), one);
      
      ok = islt(n1, n);
      n  = select(ok, n1, n);
      n1 = select(ok, shri(n+a0/n, 1), n1);
      
      ok =  lt(n1, n);
      n  = select(ok, n1, n);
      n1 = select(ok, shri(n+a0/n, 1), n1);
      
      ok =  lt(n1, n);
      n  = select(ok, n1, n);
      
      A0 tmp = sub(n*sub(n, one), one);
      n  = seladd( isge(tmp+n,a0), n, Mone<A0>());
      n =  seladd(na, Zero<A0>(), n);
      
      return n;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),uint16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 const  na = isnez(a0);
      A0 const  z1 = add(shri(a0, 6), integral_constant<A0, 16>());
      A0 const  z2 = add(shri(a0,10), integral_constant<A0, 256>());
      A0 const  C1 = integral_constant<A0, 31679>(); 
      //////////////////////////////////////////////////////////////////////////
      // choose a proper starting point for approximation
      //////////////////////////////////////////////////////////////////////////
      A0 n  = select(islt(a0, C1), z1, z2);
      A0 ok =  isgtz(n);
      static A0 const one = One<A0>();
      n  = select(ok, n, one);
      
      A0 n1 = select(ok, shri(n+a0/n, 1), one);
      
      ok = islt(n1, n);
      n  = select(ok, n1, n);
      n1 = select(ok, shri(n+a0/n, 1), n1);
      
      ok = islt(n1, n);
      n  = select(ok, n1, n);
      n1 = select(ok, shri(n+a0/n, 1), n1);
      
      ok =  islt(n1, n);
      n  = select(ok, n1, n);
      n  = seladd( isgt(n*n,a0), n, Mone<A0>());
      
      return seladd(na, Zero<A0>(), n);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),uint8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 const na  = isnez(a0);
      A0 n   = add(shri(a0, 4), Four<A0>());
      A0 n1  = shri(n+a0/n, 1);
      A0 msk = b_and(isle(n1,n), na);
      
      n   = select(msk,n1,n);
      n1  = sqr(n);
      msk = b_or(isgt(n1,a0), b_and(iseqz(n1), na));
      n   = seladd( msk, n, Mone<A0>());
      
      return seladd(na, Zero<A0>(), n);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sqrt_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,signed>::type     int_type;
      typedef typename meta::as_integer<A0,unsigned>::type  uint_type;
      return seladd(isgtz(a0), Zero<int_type>(), simd::native_cast<int_type>(sqrt(simd::native_cast<uint_type>(a0))));      
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
