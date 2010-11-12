//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_EXP2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_EXP2_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/toolbox/exponential/function/scalar/impl/expo.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for exp2

  /////////////////////////////////////////////////////////////////////////////
  // Compute exp2(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<exp2_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  real_)
    {
      return impl::exponential<A0,two_tag, tag::not_simd_type, accu_tag>::expa(a0); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
//       typedef int itype; 
//       if (itype(a0) > itype(Maxexponent<type>())) return Inf<type>();
//       if (itype(a0) <= itype(Minexponent<type>())) return Zero<type>(); 
      return ldexp(One<type>(), a0); 
    }
  };
} }


      
#endif
