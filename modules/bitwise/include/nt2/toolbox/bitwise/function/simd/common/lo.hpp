//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_LO_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_LO_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lo_, tag::cpu_,
                     (A0)(X),
                     ((simd_<arithmetic_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::lo_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      typedef typename meta::scalar_of<result_type>::type int_type;

      BOOST_STATIC_CONSTANT(int_type, shift = sizeof(int_type)*4);
      BOOST_STATIC_CONSTANT(int_type, pattern = (int_type(int_type(-1)<<shift))>>shift);

      return b_and(integral_constant<result_type,pattern>(),a0);
    }

  };
} }

#endif
// modified by jt the 04/01/2011