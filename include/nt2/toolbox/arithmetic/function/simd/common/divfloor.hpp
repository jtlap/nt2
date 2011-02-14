//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_DIVFLOOR_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_DIVFLOOR_HPP_INCLUDED



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::divfloor_, tag::cpu_,
                            (A0)(X),
                            ((simd_<arithmetic_<A0>,X>))
                            ((simd_<arithmetic_<A0>,X>))
                           );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::divfloor_(tag::simd_<tag::arithmetic_, X> ,
                              tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2){ return -divceil(-a0,a1); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::divfloor_, tag::cpu_,
                            (A0)(X),
                            ((simd_<unsigned_<A0>,X>))
                            ((simd_<unsigned_<A0>,X>))
                           );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::divfloor_(tag::simd_<tag::unsigned_, X> ,
                              tag::simd_<tag::unsigned_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2){ return rdivide(a0,a1); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::divfloor_, tag::cpu_,
                            (A0)(X),
                            ((simd_<real_<A0>,X>))
                            ((simd_<real_<A0>,X>))
                           );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::divfloor_(tag::simd_<tag::real_, X> ,
                              tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2){ return floor(a0/a1); }
  };
} }

#endif
// modified by jt the 14/01/2011
