//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SIN_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SIN_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo.hpp>
//  MIGRATION WARNING you have to provide the file for the previous include from
//  nt2/core/numeric/function/details/scalar/impl/trigo.hpp
//  of the old nt2

namespace nt2 { namespace functors
{

  //  no special validate for sin

  /////////////////////////////////////////////////////////////////////////////
  // Compute sin(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sin_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_, arithmetic_))
      )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  real_)
    {
       return impl::trig_base<A0,radian_tag, trig_tag, tag::not_simd_type>::sina(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::sin(type(a0)); 
    }
  };
} }


      
#endif
