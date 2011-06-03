//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_SUBS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_SUBS_HPP_INCLUDED
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/adds.hpp>
#include <nt2/include/functions/any.hpp>
#ifdef NT2_SIMD_DETECTED

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::subs_, tag::cpu_,
                          (A0)(X),
                          ((simd_<real_<A0>,X>))
                          ((simd_<real_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::subs_(tag::simd_<tag::real_, X>,
			 tag::simd_<tag::real_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};
      
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::sub(a0, a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::subs_, tag::cpu_,
                          (A0)(X),
                          ((simd_<uint_<A0>,X>))
                          ((simd_<uint_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::subs_(tag::simd_<tag::uint_, X>,
			 tag::simd_<tag::uint_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};
      
    NT2_FUNCTOR_CALL(2)
    {
      A0 a0ma1 = a0-a1;
      return b_and(a0ma1, le(a0ma1, a0)); 
      //      return seladd(gt(a0, a1), Zero<A0>(), a0-a1); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::subs_, tag::cpu_,
                          (A0)(X),
                          ((simd_<int_<A0>,X>))
                          ((simd_<int_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::subs_(tag::simd_<tag::int_, X>,
			 tag::simd_<tag::int_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 res =  adds(a0, -a1); 
      if (nt2::any(eq(a1, Valmin<A0>())))
	return sel(eq(a1, Valmin<A0>()), adds(adds(a0, Valmax<A0>()),One<A0>()), res);
      else
	return res; 
    }
  };
} }

#endif
#endif
