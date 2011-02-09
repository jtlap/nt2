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
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return map(functor<tag::shli_>(), a0, splat(a1)); //TO BE CONFIRMED
    }
  };
} }

#endif
// modified by jt the 04/01/2011
// modified manually by jt the 05/01/2011    
