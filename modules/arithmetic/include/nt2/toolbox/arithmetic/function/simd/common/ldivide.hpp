//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_LDIVIDE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_LDIVIDE_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/rdivide.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ldivide_, tag::cpu_,
                          (A0)(X),
                          ((simd_<arithmetic_<A0>,X>))
                          ((simd_<arithmetic_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ldivide_(tag::simd_<tag::arithmetic_, X> ,
                            tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
//       const A0 iseqza0 = is_eqz(a0);
//       return (a1-(iseqza0&a1))/(a0+(iseqza0&One<A0>()));
      return rdivide(a1, a0); 
    }

  };
} }


#endif
// modified by jt the 04/01/2011
