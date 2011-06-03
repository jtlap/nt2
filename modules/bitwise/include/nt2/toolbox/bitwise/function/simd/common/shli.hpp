//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SHLI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SHLI_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                       (A0)(A1)(X),
                       ((simd_<arithmetic_<A0>,X>))
                       ((integer_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::shli_(tag::simd_<tag::arithmetic_, X> ,
                         tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_unsigned<A0>::type ntype;
      return simd::native_cast<A0>(
        map( functor<tag::shift_left_>()
           , simd::native_cast<ntype>(a0)
           , splat<ntype>(a1)
           )
      );
    }
  };
} }

#endif
// modified by mg the 03/05/2011
