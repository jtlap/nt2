//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_CORRECT_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_CORRECT_FMA_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/two_prod.hpp>
#include <nt2/include/functions/two_add.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::correct_fma_, tag::cpu_,
                              (A0)(X),
                              ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::correct_fma_(tag::simd_<tag::arithmetic_, X> ,
                                tag::simd_<tag::arithmetic_, X> ,
                                tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(3)
    {
      return a0*a1+a2;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::correct_fma_, tag::cpu_,
                              (A0)(X),
                              ((simd_<real_<A0>,X>))
                              ((simd_<real_<A0>,X>))
                              ((simd_<real_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::correct_fma_(tag::simd_<tag::real_, X> ,
                                tag::simd_<tag::real_, X> ,
                                tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(3)
    {
      A0 p, rp, s, rs;
      boost::fusion::tie(p, rp) = two_prod(a0, a1);
      boost::fusion::tie(s, rs) = two_add(p, a2);
      return s+(rp+rs);
    }
  };
} }

#endif
// modified by jt the 04/01/2011
