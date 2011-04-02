//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_TAN_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_TAN_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
 #include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo.hpp>
//  MIGRATION WARNING you have to provide the file for the previous include from
//  nt2/core/numeric/function/details/simd/common/impl/trigo.hpp
//  of the old nt2



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_tan_, tag::cpu_,
                           (A0)(X),
                           ((simd_<arithmetic_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_tan_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return is_nez(simd::native_cast<type>(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_tan_, tag::cpu_,
                           (A0)(X),
                           ((simd_<real_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_tan_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return impl::trig_base<A0,radian_tag, fast_tag, tag::simd_type>::tana(a0);
    }
  };
} }

#endif
// modified by jt the 05/01/2011